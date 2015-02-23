//===-- lib/galaxy/ast/ASTNode.cpp - class definition ------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the ASTNode class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/ASTNode.h"
using namespace Galaxy;

ASTNode::ASTNode(const ASTNode::Kind& kind) : kind(kind) { }

ASTNode::ASTNode(const ASTNode& orig) : kind(orig.getKind()) { }

ASTNode::~ASTNode() { }

const ASTNode::Kind& ASTNode::getKind() const {
    return kind;
}

ASTNode* ASTNode::clone() const {
    return new ASTNode(*this);
}

std::string ASTNode::toString() const {
    return "()";
}

void* ASTNode::accept(ASTVisitor* visitor) {
    return visitor->visit(*this);
}

llvm::raw_ostream& Galaxy::operator<<(llvm::raw_ostream& out,
        const ASTNode& node) {
    return out << node.toString();
}
