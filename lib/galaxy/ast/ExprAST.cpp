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

#include "galaxy/ast/ExprAST.h"
using namespace Galaxy;

llvm::IRBuilder<> ExprAST::builder =
        llvm::IRBuilder<>(llvm::getGlobalContext());

ExprAST::ExprAST() { }

ExprAST::ExprAST(const ExprAST& orig) { }

ExprAST::~ExprAST() { }

ExprAST* ExprAST::clone() const {
    return new ExprAST(*this);
}

std::string ExprAST::toString() const {
    return "()";
}

llvm::Value* ExprAST::toCode() const {
    const unsigned bits = 1;
    const unsigned value = 0;
    return llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(bits, value));
}

llvm::raw_ostream& Galaxy::operator<<(llvm::raw_ostream& out,
        const ExprAST& expr) {
    return out << expr.toString();
}
