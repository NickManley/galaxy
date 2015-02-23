//===-- include/galaxy/ast/VariableExprAST.h ---------------*- C++ -*-===//
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
/// VariableExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_VARIABLEEXPRAST_H
#define GALAXY_AST_VARIABLEEXPRAST_H
#include "ExprAST.h"

namespace Galaxy {

class VariableExprAST : public ExprAST {
protected:
    const std::string name;

public:
    /// \brief Constructor.
    explicit VariableExprAST(const std::string& name);

    /// \brief Copy constructor.
    VariableExprAST(const VariableExprAST& orig);

    /// \brief Destructor.
    virtual ~VariableExprAST();

    static bool classof(const ASTNode* node);

    const std::string& getName() const;

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual VariableExprAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void* accept(ASTVisitor* visitor);

}; // END class VariableExprAST

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_VARIABLEEXPRAST_H
