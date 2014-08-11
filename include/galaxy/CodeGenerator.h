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
#include <llvm/Analysis/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

namespace Galaxy {

class BinaryExprAST;
class FunctionAST;
class NegativeExprAST;
class NumberExprAST;
class PrototypeAST;

class CodeGenerator : public ASTVisitor {
public:
    static llvm::IRBuilder<> builder;
    static llvm::Module* module;
    void* result;

    /// \brief Constructor.
    explicit CodeGenerator();

    /// \brief Copy constructor.
    CodeGenerator(const CodeGenerator& orig);

    /// \brief Destructor.
    virtual ~CodeGenerator();

    llvm::Value* getValue(ExprAST *expr);
    llvm::Function* getPrototype(PrototypeAST *proto);
    llvm::Function* getFunction(FunctionAST *func);
    llvm::Function* getFunction(ExprAST *expr);

    void visit(const ExprAST& ast);
    void visit(const BinaryExprAST& ast);
    void visit(const FunctionAST& ast);
    void visit(const NegativeExprAST& ast);
    void visit(const NumberExprAST& ast);
    void visit(const PrototypeAST& ast);
};

} // END namespace Galaxy

#endif // END ifndef GALAXY_CODEGENERATOR_H
