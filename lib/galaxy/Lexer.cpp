//===-- lib/galaxy/Lexer.cpp - Lexer class definition ------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the Lexer class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/Lexer.h"
using namespace Galaxy;

Lexer::Lexer(const std::string& input)
        : src(input), len(input.length()), idx(0) { }

Lexer::Lexer(const Lexer& orig)
        : src(orig.src), len(orig.len), idx(orig.idx) { }

Lexer::~Lexer() { }

Token Lexer::consume() {
    return lexToken();
}

// The peek method should not affect the idx value.
// Therefore, we create a copy of it before lexing
// and then reassign idx to its original value
// before returning.
Token Lexer::peek() {
    std::size_t orig_idx = idx;
    Token token = lexToken();
    idx = orig_idx;
    return token;
}

Token Lexer::peekAhead() {
    std::size_t orig_idx = idx;
    lexToken(); // ignore current
    Token token = lexToken();
    idx = orig_idx;
    return token;
}

Token Lexer::lexToken() {
    lexToken_start:
    if (idx >= len) {
        return Token(TokenType::END_FILE);
    }
    if (Lexer::isWhitespace(src[idx])) {
        idx++;
        goto lexToken_start;
    }
    if (Lexer::isDigit(src[idx])) {
        return lexNumber();
    }
    if (Lexer::isBinOp(src[idx])) {
        return lexBinOp();
    }
    if (Lexer::isParen(src[idx])) {
        return Token(src[idx++], TokenType::PAREN);
    }
    return Token(TokenType::ERR);
}

Token Lexer::lexBinOp() {
    return Token(src[idx++], TokenType::BINOP);
}

Token Lexer::lexNumber() {
    std::string result;
    for (auto it = src.cbegin()+idx; isDigit(*it); it++) {
        result.append(1, *it);
        idx++;
    }
    return Token(result, TokenType::NUMBER);
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isBinOp(char c) {
    return c == '+'
        || c == '-'
        || c == '*'
        || c == '/';
}

bool Lexer::isWhitespace(char c) {
    return c == ' '
        || c == '\t'
        || c == '\r'
        || c == '\n';
}

bool Lexer::isParen(char c) {
    return c == '(' || c == ')';
}
