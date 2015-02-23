//===-- lib/galaxy/ast/VarStmtAST.cpp ----------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the VarStmtAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/VarStmtAST.h"
#include "galaxy/ast/ExprAST.h"
using namespace Galaxy;

VarStmtAST::VarStmtAST(const std::string& name, ExprAST* expr)
    : StmtAST(ASTNode::Kind::VAR_STMT), name(name), expr(expr) { }

VarStmtAST::VarStmtAST(const VarStmtAST& orig)
    : StmtAST(orig), name(orig.name), expr(orig.expr->clone()) { }

VarStmtAST::~VarStmtAST() { }

bool VarStmtAST::classof(const ASTNode* node) {
    return node->getKind() == ASTNode::Kind::VAR_STMT;
}

const std::string& VarStmtAST::getName() const {
    return this->name;
}

ExprAST* VarStmtAST::getExpr() const {
    return this->expr;
}

VarStmtAST* VarStmtAST::clone() const {
    return new VarStmtAST(*this);
}

std::string VarStmtAST::toString() const {
    return this->name;
}

void* VarStmtAST::accept(ASTVisitor* visitor) {
    return visitor->visit(*this);
}
