//===-- lib/galaxy/CodeGenerator.cpp - Definition ----------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the CodeGenerator class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/CodeGenerator.h"
using namespace Galaxy;

llvm::IRBuilder<> CodeGenerator::builder =
        llvm::IRBuilder<>(llvm::getGlobalContext());

CodeGenerator::CodeGenerator() { }

CodeGenerator::CodeGenerator(const CodeGenerator& orig) { }

CodeGenerator::~CodeGenerator() { }

llvm::Value* CodeGenerator::getValue(ExprAST *expr) {
    expr->accept(this);
    return (llvm::Value*)result;
}

// Do nothing for base class ExprAST.
void CodeGenerator::visit(const ExprAST& ast) { }

void CodeGenerator::visit(const BinaryExprAST& ast) {
    const unsigned bits = 32;
    llvm::Value *leftValue = getValue(ast.getLhs());
    llvm::Value *rightValue = getValue(ast.getRhs());
    const std::string& op = ast.getOp();

    if (op == "+") {
        result = builder.CreateAdd(leftValue, rightValue, "addtmp");
    } else if (op == "-") {
        result = builder.CreateSub(leftValue, rightValue, "subtmp");
    } else if (op == "*") {
        result = builder.CreateMul(leftValue, rightValue, "multmp");
    } else if (op == "/") {
        result = builder.CreateSDiv(leftValue, rightValue, "divtmp");
    } else {
        result = llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(bits, 0));
    }
}

void CodeGenerator::visit(const NumberExprAST& ast) {
    const unsigned bits = 32;
    const uint8_t radix = 10;
    result = llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(bits, ast.getValue(), radix));
}
