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

#include "galaxy/ast/BinaryExprAST.h"
#include "galaxy/ast/NegativeExprAST.h"
#include "galaxy/ast/NumberExprAST.h"
#include "galaxy/ast/VariableExprAST.h"
#include "galaxy/ast/VarStmtAST.h"
#include "galaxy/Lexer.h"
#include "galaxy/Parser.h"
using namespace Galaxy;

Parser::Parser(const std::string& src)
        : lexer(new Lexer(src)) { }

Parser::Parser(const Parser& orig)
        : lexer(new Lexer(*(orig.lexer))),
        errors(Parser::copyErrors(orig.errors)) { }

Parser::~Parser() {
    delete lexer;
    for(auto e : errors) {
        delete e;
    }
    errors.clear();
}

ASTNode* Parser::parse() {
    Token token = lexer->peek();
    if (token.getType() == TokenType::KEYWORD) {
        return parseStmt();
        //return NULL;
    }
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

ExprAST* Parser::parseNumberExpr() {
    Token token = lexer->consume();
    if (token.getValue() == "-") { return parseNegativeExpr(); }
    assert(token.getType() == TokenType::NUMBER);
    return new NumberExprAST(token.getValue());
}

ExprAST* Parser::parseNegativeExpr() {
    ExprAST *term = parseTerm();
    if (!term) {
        errors.push_back(new ParseError(ParseErrorType::EXPECTED_TERM,
                "Syntax Error (" + lexer->location().toString() +
                "): Expected term after unary minus."));
        return NULL;
    }
    return new NegativeExprAST(term);
}

ExprAST* Parser::parseTerm() {
    Token token = lexer->peek();
    if (token.getType() == TokenType::NUMBER
            || token.getValue() == "-") {
        return parseNumberExpr();
    }
    if (token.getType() == TokenType::IDENT) {
        return new VariableExprAST(lexer->consume().getValue());
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

        if (op.getType() != TokenType::BINOP) {
            errors.push_back(new ParseError(
                    ParseErrorType::EXPECTED_BINOP_OR_END,
                    "Syntax Error (" + lexer->location().toString() +
                    "): Expected binary operator or end of expression."));
            delete lhs;
            return NULL;
        }

        if (op.getValue() == "="
                && lhs->getKind() != ASTNode::Kind::VARIABLE_EXPR) {
            errors.push_back(new ParseError(
                    ParseErrorType::EXPECTED_IDENT_LHS,
                    "Syntax Error (" + lexer->location().toString() +
                    "): Expected identifier for assignment."));
            delete lhs;
            return NULL;
        }

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
            delete rhs;
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

StmtAST* Parser::parseStmt() {
    Token token = lexer->consume();
    if (token.getValue() == "var") {
        return parseVarStmt();
    }
    addError(ParseErrorType::UNEXPECTED_TOKEN,
             "Unexpected token at start of statement.");
    return NULL;
}

StmtAST* Parser::parseVarStmt() {
    Token token;
    std::string name;

    // Parse identifier name.
    token = lexer->consume();
    if (token.getType() != TokenType::IDENT) {
        addError(ParseErrorType::EXPECTED_IDENT_LHS,
                 "Expected identifier for assignment.");
        return NULL;
    }
    name = token.getValue();

    // Parse assignment operator.
    token = lexer->consume();
    if (token.getType() != TokenType::BINOP ||
        token.getValue() != "=")
    {
        addError(ParseErrorType::EXPECTED_BINOP,
                 "Expected assignment operator.");
        return NULL;
    }

    // Parse expression.
    ExprAST* expr = parseExpr();
    if (!expr) { return NULL;}

    return new VarStmtAST(name, expr);
}

bool Parser::hasErrors() {
    return errors.size() > 0;
}

void Parser::addError(ParseErrorType type, const std::string& message) {
    errors.push_back(new ParseError(type,
            "Syntax Error (" + lexer->location().toString() + "): " +
            message));
}

ParseError* Parser::popError() {
    if (errors.size() > 0) {
        auto e = errors.front();
        errors.pop_front();
        return e;
    }
    return NULL;
}

std::list<ParseError*> Parser::copyErrors(std::list<ParseError*> errors) {
    std::list<ParseError*> errorsCopy;
    for (auto e : errors) {
        errorsCopy.push_back((ParseError*)e->clone());
    }
    return errorsCopy;
}

bool Parser::isEndOfExpr(const Token& t) {
    return t.getType() == TokenType::END_FILE || t.getValue() == ")";
}

bool Parser::isBinOp(const Token& t) {
    return t.getType() == TokenType::BINOP;
}
