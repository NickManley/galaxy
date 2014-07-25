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
        : lexer(new Lexer(*(orig.lexer))) { }

Parser::~Parser() {
    delete lexer;
}

ExprAST* Parser::parse() {
    return parseExpr();
}

ExprAST* Parser::parseExpr() {
    return parseBinaryExpr(0, parseTerm());
}

NumberExprAST* Parser::parseNumberExpr() {
    Token token = lexer->consume();
    if (token.getValue() == "-") { return parseNegativeExpr(); }
    assert(token.getType() == TokenType::NUMBER);
    return new NumberExprAST(token.getValue());
}

NumberExprAST* Parser::parseNegativeExpr() {
    Token token = lexer->consume();
    assert(token.getType() == TokenType::NUMBER);
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
    return NULL;
}

// Implemented using precedence climbing.
ExprAST* Parser::parseBinaryExpr(int prec, ExprAST *lhs) {
    // The binary expression ends when we reach the
    // end of the program or a closing parenthesis.
    auto isEnd = [] (const Token& t) -> bool {
        return t.getType() == TokenType::END_FILE
                || t.getValue() == ")";
    };
    auto isBinOp = [] (const Token& t) -> bool {
        return t.getType() == TokenType::BINOP;
    };

    while (true) {
        Token op = lexer->consume();
        if (isEnd(op)) { break; }

        // If the current operator being read has a
        // weaker precedence than the previous one (prec),
        // then we return the left-hand side as its own ExprAST.
        if (op.getPrec() < prec) { return lhs; }
        // Parse the right hand side of the expression.
        ExprAST *rhs = parseTerm();

        Token nextOp = lexer->peek();
        if (isBinOp(nextOp) && op.getPrec() < nextOp.getPrec()) {
            rhs = parseBinaryExpr(op.getPrec(), rhs);
        }
        lhs = new BinaryExprAST(op.getValue(), lhs, rhs);
    }
    return lhs;
}
