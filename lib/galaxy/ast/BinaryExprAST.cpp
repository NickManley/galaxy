//===-- lib/galaxy/ast/BinaryExprAST.cpp -------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the BinaryExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/BinaryExprAST.h"
using namespace Galaxy;

BinaryExprAST::BinaryExprAST(const std::string op,
    ExprAST *lhs, ExprAST *rhs)
    : op(op), lhs(lhs), rhs(rhs) { }

BinaryExprAST::BinaryExprAST(const BinaryExprAST& orig)
    : ExprAST(orig), op(orig.op),
      lhs(orig.lhs->clone()), rhs(orig.rhs->clone()) { }

BinaryExprAST::~BinaryExprAST() {
    delete lhs;
    delete rhs;
}

std::string BinaryExprAST::toString() const {
    return "(" + this->op + " " + this->lhs->toString()
            + " " + this->rhs->toString() + ")";
}
