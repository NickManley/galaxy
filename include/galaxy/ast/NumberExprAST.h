//===-- include/galaxy/ast/NumberExprAST.h -----------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the NumberExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_NUMBEREXPRAST_H
#define GALAXY_AST_NUMBEREXPRAST_H
#include "ExprAST.h"

namespace Galaxy {

class NumberExprAST : public ExprAST {
protected:
    const std::string value;

public:
    /// \brief Constructor.
    explicit NumberExprAST(const std::string& value);

    /// \brief Copy constructor.
    NumberExprAST(const NumberExprAST& orig);

    /// \brief Destructor.
    virtual ~NumberExprAST();

    const std::string& getValue() const;

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual ExprAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void accept(ASTVisitor* visitor);

}; // END class NumberExprAST

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_NUMBEREXPRAST_H
