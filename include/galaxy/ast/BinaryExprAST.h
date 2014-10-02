//===-- include/galaxy/ast/BinaryExprAST.h -----------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the BinaryExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_BINARYEXPRAST_H
#define GALAXY_AST_BINARYEXPRAST_H
#include "ExprAST.h"

namespace Galaxy {

class BinaryExprAST : public ExprAST {
protected:
    const std::string op;
    ExprAST *lhs, *rhs;

public:
    /// \brief Constructor.
    explicit BinaryExprAST(const std::string op, ExprAST *lhs, ExprAST *rhs);

    /// \brief Copy constructor.
    BinaryExprAST(const BinaryExprAST& orig);

    /// \brief Destructor.
    virtual ~BinaryExprAST();

    static bool classof(const ASTNode* node);

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual BinaryExprAST* clone() const;

    const std::string& getOp() const;
    ExprAST* getLhs() const;
    ExprAST* getRhs() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void accept(ASTVisitor* visitor);

}; // END class BinaryExprAST

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_BINARYEXPRAST_H
