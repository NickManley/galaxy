//===-- include/galaxy/CodeGenerator.h - Declaration --------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the CodeGenerator class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_CODEGENERATOR_H
#define GALAXY_CODEGENERATOR_H
#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/CodeGenError.h"
#include <llvm/Analysis/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <list>

namespace Galaxy {

class ASTNode;
class ExprAST;
class BinaryExprAST;
class FunctionAST;
class NegativeExprAST;
class NumberExprAST;
class PrototypeAST;
class VariableExprAST;
class StmtAST;
class VarStmtAST;

class CodeGenerator : public ASTVisitor {
public:
    static llvm::IRBuilder<> builder;
    static llvm::Module* module;
    static std::map<std::string, llvm::GlobalVariable*> globalValues;
    std::list<CodeGenError*> errors;
    void* result;

    /// \brief Constructor.
    explicit CodeGenerator();

    /// \brief Copy constructor.
    CodeGenerator(const CodeGenerator& orig);

    /// \brief Destructor.
    virtual ~CodeGenerator();

    llvm::Value* generateValue(ExprAST *expr);
    llvm::Function* generateFunction(ASTNode *node);
    llvm::Function* generateFunction(FunctionAST *func);
    llvm::Function* generateFunction(PrototypeAST *proto);

    void visit(const ASTNode& ast);
    void visit(const BinaryExprAST& ast);
    void visit(const FunctionAST& ast);
    void visit(const NegativeExprAST& ast);
    void visit(const NumberExprAST& ast);
    void visit(const PrototypeAST& ast);
    void visit(const VariableExprAST& ast);
    void visit(const VarStmtAST& ast);

    void addError(CodeGenErrorType type, const std::string& message);
    CodeGenError* popError();
};

} // END namespace Galaxy

#endif // END ifndef GALAXY_CODEGENERATOR_H
