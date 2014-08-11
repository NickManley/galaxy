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

#include "galaxy/ast/BinaryExprAST.h"
#include "galaxy/ast/FunctionAST.h"
#include "galaxy/ast/NegativeExprAST.h"
#include "galaxy/ast/NumberExprAST.h"
#include "galaxy/ast/PrototypeAST.h"
#include "galaxy/CodeGenerator.h"
using namespace Galaxy;

llvm::IRBuilder<> CodeGenerator::builder =
        llvm::IRBuilder<>(llvm::getGlobalContext());
llvm::Module* CodeGenerator::module = new llvm::Module("GX",
        llvm::getGlobalContext());

CodeGenerator::CodeGenerator() { }

CodeGenerator::CodeGenerator(const CodeGenerator& orig) { }

CodeGenerator::~CodeGenerator() { }

llvm::Value* CodeGenerator::getValue(ExprAST *expr) {
    expr->accept(this);
    return (llvm::Value*)result;
}

llvm::Function* CodeGenerator::getPrototype(PrototypeAST* proto) {
    proto->accept(this);
    return (llvm::Function*)result;
}

llvm::Function* CodeGenerator::getFunction(FunctionAST* func) {
    func->accept(this);
    return (llvm::Function*)result;
}

llvm::Function* CodeGenerator::getFunction(ExprAST* expr) {
    FunctionAST *f = new FunctionAST(expr);
    llvm::Function *result = getFunction(f);
    delete f;
    return result;
}

// Report error and exit for base class ExprAST.
// If we got here, then it means the virtual methods
// for the visitor pattern weren't declared/defined
// properly.
void CodeGenerator::visit(const ExprAST& ast) {
    llvm::errs() << "FATAL: ASTVisitor not properly declared!\n";
    llvm::errs().flush();
    exit(1);
}

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

void CodeGenerator::visit(const FunctionAST& ast) {
    PrototypeAST *proto = ast.getPrototype();
    ExprAST *expr = ast.getExpr();
    llvm::Function *func = this->getPrototype(proto);
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(
            llvm::getGlobalContext(), "entry", func);
    builder.SetInsertPoint(bb);
    builder.CreateRet(this->getValue(expr));
    llvm::verifyFunction(*func);
    result = func;
}

void CodeGenerator::visit(const NegativeExprAST& ast) {
    result = builder.CreateNeg(getValue(ast.getTerm()));
}

void CodeGenerator::visit(const NumberExprAST& ast) {
    const unsigned bits = 32;
    const uint8_t radix = 10;
    result = llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(bits, ast.getValue(), radix));
}

void CodeGenerator::visit(const PrototypeAST& ast) {
    // Create the argument types
    std::vector<llvm::Type*> arguments(ast.getArgs().size(),
            llvm::Type::getInt32Ty(llvm::getGlobalContext()));
    // Create the function prototype by specifying the
    // return type, arguments, and whether it is vararg.
    llvm::FunctionType *funcType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(llvm::getGlobalContext()),
            arguments, false);
    // Create the function itself.
    result = llvm::Function::Create(funcType,
            llvm::Function::ExternalLinkage, ast.getName(), module);
}
