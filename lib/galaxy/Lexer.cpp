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
#include <cassert>
using namespace Galaxy;

Lexer::Lexer(const std::string& input)
        : src(input), len(input.length()), idx(0), loc(1, 0) { }

Lexer::Lexer(const Lexer& orig)
        : src(orig.src), len(orig.len), idx(orig.idx), loc(orig.loc) { }

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
    SourceLocation orig_loc = loc;
    Token token = lexToken();
    idx = orig_idx;
    loc = orig_loc;
    return token;
}

Token Lexer::peekAhead() {
    std::size_t orig_idx = idx;
    SourceLocation orig_loc = loc;
    lexToken(); // ignore current
    Token token = lexToken();
    idx = orig_idx;
    loc = orig_loc;
    return token;
}

const SourceLocation Lexer::location() {
    return SourceLocation(loc);
}

Token Lexer::lexToken() {
    lexToken_start:
    if (idx >= len) {
        return Token(TokenType::END_FILE);
    }
    if (Lexer::isWhitespace(src[idx])) {
        if (src[idx] == '\n') {
            loc.line++;
            loc.col = 0;
        } else {
            loc.col++;
        }
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
        loc.col++;
        return Token(src[idx++], TokenType::PAREN);
    }
    if (Lexer::isAlpha(src[idx])) {
        return lexIdent();
    }
    return Token(TokenType::ERR);
}

Token Lexer::lexBinOp() {
    loc.col++;
    return Token(src[idx++], TokenType::BINOP);
}

Token Lexer::lexNumber() {
    std::string result;
    for (auto it = src.cbegin()+idx; isDigit(*it); it++) {
        result.append(1, *it);
        idx++;
        loc.col++;
    }
    return Token(result, TokenType::NUMBER);
}

Token Lexer::lexIdent() {
    assert(isAlpha(src[idx]));
    std::string result;
    for (auto it = src.cbegin()+idx; isAlphaOrDigit(*it); it++) {
        result.append(1, *it);
        idx++;
        loc.col++;
    }
    return Token(result, TokenType::IDENT);
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlphaOrDigit(char c) {
    return isAlpha(c) || isDigit(c);
}

bool Lexer::isBinOp(char c) {
    return c == '='
        || c == '+'
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
