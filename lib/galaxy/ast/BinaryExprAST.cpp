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

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/BinaryExprAST.h"
using namespace Galaxy;

BinaryExprAST::BinaryExprAST(const std::string op,
    ExprAST *lhs, ExprAST *rhs)
    : ExprAST(ASTNode::Kind::BINARY_EXPR), op(op), lhs(lhs), rhs(rhs) { }

BinaryExprAST::BinaryExprAST(const BinaryExprAST& orig)
    : ExprAST(orig), op(orig.op),
      lhs(orig.lhs->clone()), rhs(orig.rhs->clone()) { }

BinaryExprAST::~BinaryExprAST() {
    delete lhs;
    delete rhs;
}

bool BinaryExprAST::classof(const ExprAST* ast) {
    return ast->getKind() == ASTNode::Kind::BINARY_EXPR;
}

BinaryExprAST* BinaryExprAST::clone() const {
    return new BinaryExprAST(*this);
}

const std::string& BinaryExprAST::getOp() const {
    return op;
}

ExprAST* BinaryExprAST::getLhs() const {
    return lhs;
}

ExprAST* BinaryExprAST::getRhs() const {
    return rhs;
}

std::string BinaryExprAST::toString() const {
    return "(" + this->op + " " + this->lhs->toString()
            + " " + this->rhs->toString() + ")";
}

void BinaryExprAST::accept(ASTVisitor* visitor) {
    visitor->visit(*this);
}
