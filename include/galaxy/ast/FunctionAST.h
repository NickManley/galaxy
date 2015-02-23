//===-- include/galaxy/ast/FunctionAST.h -------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the FunctionAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_FUNCTIONAST_H
#define GALAXY_AST_FUNCTIONAST_H
#include <llvm/Support/raw_ostream.h>
#include <string>

namespace Galaxy {

class ASTVisitor;
class ASTNode;
class PrototypeAST;

class FunctionAST {
protected:
    PrototypeAST *prototype;
    ASTNode *node;
public:
    /// \brief Constructor.
    explicit FunctionAST(PrototypeAST *proto, ASTNode *node);

    /// \brief Constructor.
    explicit FunctionAST(ASTNode *node);

    /// \brief Copy constructor.
    FunctionAST(const FunctionAST& orig);

    /// \brief Destructor.
    virtual ~FunctionAST();

    PrototypeAST* getPrototype() const;
    ASTNode* getNode() const;

    /// \brief Clone method.
    virtual FunctionAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void* accept(ASTVisitor* visitor);

    /// \brief Overload stream insertion operator.
    friend llvm::raw_ostream& operator<<(
            llvm::raw_ostream& out, const FunctionAST& func);
}; // END class FunctionAST

llvm::raw_ostream& operator<<(llvm::raw_ostream& out,
        const FunctionAST& func);

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_FUNCTIONAST_H
