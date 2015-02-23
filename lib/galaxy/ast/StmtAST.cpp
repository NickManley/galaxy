//===-- lib/galaxy/ast/StmtAST.cpp - class definition ------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the StmtAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/StmtAST.h"
using namespace Galaxy;

StmtAST::StmtAST() : ASTNode(ASTNode::Kind::STMT) { }

StmtAST::StmtAST(const ASTNode::Kind& kind) : ASTNode(kind) { }

StmtAST::StmtAST(const StmtAST& orig) : ASTNode(orig) { }

StmtAST::~StmtAST() { }

bool StmtAST::classof(const ASTNode* node) {
    return node->getKind() >= ASTNode::Kind::STMT &&
           node->getKind() <= ASTNode::Kind::STMT_LAST;
}

StmtAST* StmtAST::clone() const {
    return new StmtAST(*this);
}

std::string StmtAST::toString() const {
    return "(_)";
}

void* StmtAST::accept(ASTVisitor* visitor) {
    return visitor->visit(*this);
}

llvm::raw_ostream& Galaxy::operator<<(llvm::raw_ostream& out,
        const StmtAST& stmt) {
    return out << stmt.toString();
}
