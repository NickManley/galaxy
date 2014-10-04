//===-- lib/galaxy/ast/FunctionAST.cpp - Definition --------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the FunctionAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ASTNode.h"
#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/FunctionAST.h"
#include "galaxy/ast/PrototypeAST.h"
using namespace Galaxy;

FunctionAST::FunctionAST() { }

FunctionAST::FunctionAST(PrototypeAST *proto, ASTNode *node)
        : prototype(proto->clone()), node(node->clone()) { }

FunctionAST::FunctionAST(ASTNode *node)
        : prototype(new PrototypeAST()), node(node->clone()) { }

FunctionAST::FunctionAST(const FunctionAST& orig)
        : prototype(orig.prototype->clone()), node(orig.node->clone()) { }

FunctionAST::~FunctionAST() {
    delete prototype;
    delete node;
}

PrototypeAST* FunctionAST::getPrototype() const {
    return prototype;
}

ASTNode* FunctionAST::getNode() const {
    return node;
}

FunctionAST* FunctionAST::clone() const {
    return new FunctionAST(*this);
}

std::string FunctionAST::toString() const {
    return prototype->toString() + " { " + node->toString() + " }";
}

void FunctionAST::accept(ASTVisitor* visitor) {
    visitor->visit(*this);
}

llvm::raw_ostream& Galaxy::operator<<(llvm::raw_ostream& out,
        const FunctionAST& func) {
    return out << func.toString();
}
