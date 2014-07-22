//===-- galaxyc/Token.cpp - Token class definition ---------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the Token class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/Token.h"
#include <cassert>
#include <iostream>
using namespace Galaxy;

Token::Token(const std::string& value, const TokenType type)
        : value(value), type(type) { }

Token::Token(const char value, const TokenType type)
        : value(std::string(1, value)), type(type) { }

Token::Token(const TokenType type)
        : type(type) { }

Token::Token(const Token& orig)
        : value(orig.value), type(orig.type) { }

Token::~Token() { }

std::ostream& Galaxy::operator<<(std::ostream& out, const Token& token) {
    return out << "TOKEN(`" << token.value << "`, "
               << TokenTypeStr.at(token.type) << ")";
}

const std::string& Token::getValue() const {
    return this->value;
}
    
const TokenType& Token::getType() const {
    return this->type;
}

int Token::getPrec() const {
    assert(this->type == TokenType::BINOP);
    auto it = Precedence.find(this->value);
    if (it == Precedence.end()) { return 0; }
    return it->second;
}
