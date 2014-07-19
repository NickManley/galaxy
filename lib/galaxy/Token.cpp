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
#include <iostream>
using namespace Galaxy;

Token::Token(const std::string& value, const TokenType type) {
    this->value = value;
    this->type = type;
}

Token::Token(const char value, const TokenType type) {
    this->value = std::string(1, value);
    this->type = type;
}

Token::Token(const TokenType type) {
    this->type = type;
}

Token::Token(const Token& orig) {
    this->value = orig.value;
    this->type = orig.type;
}

Token& Token::operator=(const Token& orig) {
    if (this == &orig) { return *this; }
    this->value = orig.value;
    this->type = orig.type;
    return *this;
}

Token::~Token() { }

std::ostream& Galaxy::operator<<(std::ostream& out, const Token& token) {
    return out << "TOKEN(`" << token.value << "`, "
               << TokenTypeStr.at(token.type) << ")";
}

const std::string& Token::getValue() const {
    return this->value;
}
    
bool Token::isType(TokenType type) const {
    return this->type == type;
}
