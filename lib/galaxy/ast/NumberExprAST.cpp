//===-- lib/galaxy/ast/NumberExprAST.cpp -------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the NumberExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/NumberExprAST.h"
using namespace Galaxy;

NumberExprAST::NumberExprAST(const std::string& value)
    : value(value) { }

NumberExprAST::NumberExprAST(const NumberExprAST& orig)
    : ExprAST(orig), value(orig.value) { }

NumberExprAST::~NumberExprAST() { }

ExprAST* NumberExprAST::clone() const {
    return new NumberExprAST(*this);
}

std::string NumberExprAST::toString() const {
    return this->value;
}
