//===-- lib/galaxy/ast/NegativeExprAST.cpp -----------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the NegativeExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/NegativeExprAST.h"
using namespace Galaxy;

NegativeExprAST::NegativeExprAST(ExprAST* term)
        : ExprAST(ExprAST::Kind::NEGATIVE), term(term) { }

NegativeExprAST::NegativeExprAST(const NegativeExprAST& orig)
        : ExprAST(orig), term(orig.term) { }

NegativeExprAST::~NegativeExprAST() { }

bool NegativeExprAST::classof(const ExprAST* ast) {
    return ast->getKind() == ExprAST::Kind::NEGATIVE;
}

ExprAST* NegativeExprAST::getTerm() const {
    return term;
}

ExprAST* NegativeExprAST::clone() const {
    return new NegativeExprAST(*this);
}

std::string NegativeExprAST::toString() const {
    return "-" + term->toString();
}

void NegativeExprAST::accept(ASTVisitor* visitor) {
    visitor->visit(*this);
}
