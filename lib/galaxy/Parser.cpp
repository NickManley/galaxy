//===-- lib/galaxy/Parser.cpp - Parser class definition ----*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the Parser class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/Parser.h"
using namespace Galaxy;

Parser::Parser(const std::string& src)
        : lexer(new Lexer(src)) { }

Parser::Parser(const Parser& orig)
        : lexer(new Lexer(*(orig.lexer))), errors(orig.errors) { }

Parser::~Parser() {
    delete lexer;
    for(auto e : errors) {
        delete e;
    }
    errors.clear();
}

ExprAST* Parser::parse() {
    return parseExpr();
}

ExprAST* Parser::parseExpr() {
    ExprAST *expr = parseTerm();
    if (!expr) {
        errors.push_back(new ParseError(ParseErrorType::UNEXPECTED_TOKEN,
            "Syntax Error (" + lexer->location().toString() +
            "): Unexpected token."));
        return NULL;
    }
    return parseBinaryExpr(0, expr);
}

NumberExprAST* Parser::parseNumberExpr() {
    Token token = lexer->consume();
    if (token.getValue() == "-") { return parseNegativeExpr(); }
    assert(token.getType() == TokenType::NUMBER);
    return new NumberExprAST(token.getValue());
}

NumberExprAST* Parser::parseNegativeExpr() {
    Token token = lexer->consume();
    if (token.getType() != TokenType::NUMBER) {
        errors.push_back(new ParseError(ParseErrorType::EXPECTED_NUMBER,
                "Syntax Error (" + lexer->location().toString() +
                "): Expected number after unary minus."));
        return NULL;
    }
    return new NumberExprAST("-" + token.getValue());
}

ExprAST* Parser::parseTerm() {
    Token token = lexer->peek();
    if (token.getType() == TokenType::NUMBER
            || token.getValue() == "-") {
        return parseNumberExpr();
    }
    if (token.getValue() == "(") {
        lexer->consume(); // eat '('
        ExprAST *expr = parseExpr();
        return expr;
    }
    if (token.getType() == TokenType::END_FILE) {
        return NULL;
    }
    return NULL;
}

// Implemented using precedence climbing.
ExprAST* Parser::parseBinaryExpr(int prec, ExprAST *lhs) {
    while (true) {
        Token op = lexer->consume();
        if (isEndOfExpr(op)) { break; }

        // If the current operator being read has a
        // weaker precedence than the previous one (prec),
        // then we return the left-hand side as its own ExprAST.
        if (op.getPrec() < prec) { return lhs; }
        // Parse the right hand side of the expression.
        ExprAST *rhs = parseTerm();
        if (!rhs) {
            errors.push_back(new ParseError(ParseErrorType::EXPECTED_TERM,
                    "Syntax Error (" + lexer->location().toString() +
                    "): Expected term after operator '" +
                    op.getValue() + "'."));
            return NULL;
        }

        Token nextOp = lexer->peek();
        if (isBinOp(nextOp) && op.getPrec() < nextOp.getPrec()) {
            rhs = parseBinaryExpr(op.getPrec(), rhs);
        }
        lhs = new BinaryExprAST(op.getValue(), lhs, rhs);
    }
    return lhs;
}

bool Parser::hasErrors() {
    return errors.size() > 0;
}

ParseError* Parser::popError() {
    if (errors.size() > 0) {
        auto e = errors.front();
        errors.pop_front();
        return e;
    }
    return NULL;
}

bool Parser::isEndOfExpr(const Token& t) {
    return t.getType() == TokenType::END_FILE || t.getValue() == ")";
}

bool Parser::isBinOp(const Token& t) {
    return t.getType() == TokenType::BINOP;
}
