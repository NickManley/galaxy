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
#define	GALAXY_CODEGENERATOR_H
#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/BinaryExprAST.h"
#include "galaxy/ast/NumberExprAST.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>

namespace Galaxy {

class CodeGenerator : public ASTVisitor {
protected:
    static llvm::IRBuilder<> builder;
public:
    void* result;

    /// \brief Constructor.
    explicit CodeGenerator();

    /// \brief Copy constructor.
    CodeGenerator(const CodeGenerator& orig);

    /// \brief Destructor.
    virtual ~CodeGenerator();

    llvm::Value* getValue(const ExprAST *expr);
    llvm::Value* getValue(ExprAST *expr);

    void visit(const ExprAST& ast);
    void visit(const BinaryExprAST& ast);
    void visit(const NumberExprAST& ast);
};

} // END namespace Galaxy

#endif // END ifndef GALAXY_CODEGENERATOR_H
