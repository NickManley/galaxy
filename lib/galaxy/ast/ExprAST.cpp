//===-- lib/galaxy/ast/ExprAST.cpp - class definition ------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the ExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/ExprAST.h"
using namespace Galaxy;

ExprAST::ExprAST() : ASTNode(ASTNode::Kind::EXPR) { }

ExprAST::ExprAST(const ASTNode::Kind& kind) : ASTNode(kind) { }

ExprAST::ExprAST(const ExprAST& orig) : ASTNode(orig) { }

ExprAST::~ExprAST() { }

bool ExprAST::classof(const ASTNode* node) {
    return node->getKind() >= ASTNode::Kind::EXPR &&
           node->getKind() <= ASTNode::Kind::EXPR_LAST;
}

ExprAST* ExprAST::clone() const {
    return new ExprAST(*this);
}

std::string ExprAST::toString() const {
    return "($)";
}

void ExprAST::accept(ASTVisitor* visitor) {
    visitor->visit(*this);
}

llvm::raw_ostream& Galaxy::operator<<(llvm::raw_ostream& out,
        const ExprAST& expr) {
    return out << expr.toString();
}
