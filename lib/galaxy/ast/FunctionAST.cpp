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

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/ExprAST.h"
#include "galaxy/ast/FunctionAST.h"
#include "galaxy/ast/PrototypeAST.h"
using namespace Galaxy;

FunctionAST::FunctionAST() { }

FunctionAST::FunctionAST(PrototypeAST *proto, ExprAST *expr)
        : prototype(proto->clone()), expr(expr->clone()) { }

FunctionAST::FunctionAST(ExprAST *expr)
        : prototype(new PrototypeAST()), expr(expr->clone()) { }

FunctionAST::FunctionAST(const FunctionAST& orig)
        : prototype(orig.prototype->clone()), expr(orig.expr->clone()) { }

FunctionAST::~FunctionAST() {
    delete prototype;
    delete expr;
}

PrototypeAST* FunctionAST::getPrototype() const {
    return prototype;
}

ExprAST* FunctionAST::getExpr() const {
    return expr;
}

FunctionAST* FunctionAST::clone() const {
    return new FunctionAST(*this);
}

std::string FunctionAST::toString() const {
    return prototype->toString() + " { " + expr->toString() + " }";
}

void FunctionAST::accept(ASTVisitor* visitor) {
    visitor->visit(*this);
}

llvm::raw_ostream& Galaxy::operator<<(llvm::raw_ostream& out,
        const FunctionAST& func) {
    return out << func.toString();
}
