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
#include "galaxy/ast/VariableExprAST.h"
#include "galaxy/ast/VarStmtAST.h"
#include "galaxy/CodeGenerator.h"
using namespace Galaxy;

llvm::IRBuilder<> CodeGenerator::builder =
        llvm::IRBuilder<>(llvm::getGlobalContext());
llvm::Module* CodeGenerator::module = new llvm::Module("GX",
        llvm::getGlobalContext());
std::map<std::string, llvm::GlobalVariable*> CodeGenerator::globalValues;

CodeGenerator::CodeGenerator() { }

CodeGenerator::CodeGenerator(const CodeGenerator& orig) { }

CodeGenerator::~CodeGenerator() { }

llvm::Value* CodeGenerator::generateValue(ExprAST* expr) {
    expr->accept(this);
    return (llvm::Value*)result;
}

llvm::Function* CodeGenerator::generateFunction(ASTNode* node) {
    FunctionAST *f = new FunctionAST(node);
    result = generateFunction(f);
    delete f;
    return (llvm::Function*)result;
}

llvm::Function* CodeGenerator::generateFunction(FunctionAST* func) {
    func->accept(this);
    return (llvm::Function*)result;
}

llvm::Function* CodeGenerator::generateFunction(PrototypeAST* proto) {
    proto->accept(this);
    return (llvm::Function*)result;
}

// Report error and exit for base class ASTNode.
// If we got here, then it means the virtual methods
// for the visitor pattern weren't declared/defined
// properly.
void CodeGenerator::visit(const ASTNode& ast) {
    llvm::errs() << "FATAL: ASTVisitor not properly declared!\n";
    llvm::errs().flush();
    exit(1);
}

void CodeGenerator::visit(const BinaryExprAST& ast) {
    const unsigned bits = 32;
    llvm::Value *leftValue = generateValue(ast.getLhs());
    llvm::Value *rightValue = generateValue(ast.getRhs());
    const std::string& op = ast.getOp();

    // Check for errors.
    // There is no need to call addError because the previous call to
    // generateValue will have already reported the errors.
    if (!leftValue || !rightValue) {
        result = NULL;
        return;
    }

    if (op == "=") {
        VariableExprAST *var = llvm::cast<VariableExprAST>(ast.getLhs());
        assert(var && globalValues[var->getName()]);
        builder.CreateStore(rightValue, globalValues[var->getName()]);
        result = rightValue;
    } else if (op == "+") {
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
    ASTNode *node = ast.getNode();
    llvm::Function *func = generateFunction(proto);
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(
            llvm::getGlobalContext(), "entry", func);
    builder.SetInsertPoint(bb);

    if (ExprAST *expr = llvm::dyn_cast<ExprAST>(node)) {
        llvm::Value *val = generateValue(expr);
        if (!val) { return; }
        builder.CreateRet(val);
    } else if (VarStmtAST *stmt = llvm::dyn_cast<VarStmtAST>(node)) {
        this->visit(*stmt);
        if (!result) { return; }
        builder.CreateRet((llvm::Value*)result);
    } else {
        auto val = llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(32, 0));
        builder.CreateRet(val);
    }

    llvm::verifyFunction(*func);
    result = func;
}

void CodeGenerator::visit(const NegativeExprAST& ast) {
    result = builder.CreateNeg(generateValue(ast.getTerm()));
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

void CodeGenerator::visit(const VariableExprAST& ast) {
    llvm::GlobalVariable *val = globalValues[ast.getName()];
    if (!val) {
        addError(CodeGenErrorType::UNDEFINED_VARIABLE,
                 "Undefined variable: " + ast.getName());
        result = NULL;
        return;
    }
    result = builder.CreateLoad(val, ast.getName().c_str());
}

void CodeGenerator::visit(const VarStmtAST& ast) {
    llvm::Value* val = generateValue(ast.getExpr());
    llvm::GlobalVariable* gvar = new llvm::GlobalVariable(*module,
            llvm::Type::getInt32Ty(llvm::getGlobalContext()),
            false,
            llvm::GlobalValue::LinkerPrivateLinkage,
            llvm::ConstantInt::get(llvm::getGlobalContext(),
                    llvm::APInt(32, 0, 10)),
            ast.getName().c_str());

    result = val;
    globalValues[ast.getName()] = gvar;
    builder.CreateStore(val, gvar);
}

void CodeGenerator::addError(CodeGenErrorType type,
            const std::string& message) {
    errors.push_back(new CodeGenError(type, message));
}

CodeGenError* CodeGenerator::popError() {
    if (errors.size() > 0) {
        auto e = errors.front();
        errors.pop_front();
        return e;
    }
    return NULL;
}
