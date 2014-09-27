//===-- include/galaxy/ast/NegativeExprAST.h ---------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the
/// NegativeExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_NEGATIVEEXPRAST_H
#define GALAXY_AST_NEGATIVEEXPRAST_H
#include "galaxy/ast/ExprAST.h"

namespace Galaxy {

class NegativeExprAST : public ExprAST {
protected:
    ExprAST *term;

public:
    /// \brief Constructor.
    explicit NegativeExprAST(ExprAST *term);

    /// \brief Copy constructor.
    NegativeExprAST(const NegativeExprAST& orig);

    /// \brief Destructor.
    virtual ~NegativeExprAST();

    static bool classof(const ExprAST* ast);

    ExprAST* getTerm() const;

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual ExprAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void accept(ASTVisitor* visitor);

}; // END class NegativeExprAST

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_NEGATIVEEXPRAST_H
