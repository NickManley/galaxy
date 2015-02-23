//===-- include/galaxy/ast/ExprAST.h - class declaration ---*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the ExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_EXPRAST_H
#define GALAXY_AST_EXPRAST_H
#include "ASTNode.h"

namespace Galaxy {

class ExprAST : public ASTNode {
public:
    /// \brief Constructor.
    explicit ExprAST();

    /// \brief Constructor with KIND.
    explicit ExprAST(const ASTNode::Kind& kind);

    /// \brief Copy constructor.
    ExprAST(const ExprAST& orig);

    /// \brief Destructor.
    virtual ~ExprAST();

    static bool classof(const ASTNode* node);

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual ExprAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void* accept(ASTVisitor* visitor);

}; // END class ExprAST

llvm::raw_ostream& operator<<(llvm::raw_ostream& out, const ExprAST& expr);

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_EXPRAST_H
