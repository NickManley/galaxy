//===-- lib/galaxy/ast/VariableExprAST.cpp -----------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the VariableExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/VariableExprAST.h"
using namespace Galaxy;

VariableExprAST::VariableExprAST(const std::string& name)
    : ExprAST(ASTNode::Kind::VARIABLE_EXPR), name(name) { }

VariableExprAST::VariableExprAST(const VariableExprAST& orig)
    : ExprAST(orig), name(orig.name) { }

VariableExprAST::~VariableExprAST() { }

bool VariableExprAST::classof(const ASTNode* node) {
    return node->getKind() == ASTNode::Kind::VARIABLE_EXPR;
}

const std::string& VariableExprAST::getName() const {
    return this->name;
}

VariableExprAST* VariableExprAST::clone() const {
    return new VariableExprAST(*this);
}

std::string VariableExprAST::toString() const {
    return this->name;
}

void* VariableExprAST::accept(ASTVisitor* visitor) {
    return visitor->visit(*this);
}
