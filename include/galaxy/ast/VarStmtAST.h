//===-- include/galaxy/ast/VarStmtAST.h --------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the VarStmtAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_VARSTMTAST_H
#define GALAXY_AST_VARSTMTAST_H
#include "StmtAST.h"

namespace Galaxy {

class ExprAST;

class VarStmtAST : public StmtAST {
protected:
    const std::string name;
    ExprAST* expr;

public:
    /// \brief Constructor.
    explicit VarStmtAST(const std::string& name, ExprAST* expr);

    /// \brief Copy constructor.
    VarStmtAST(const VarStmtAST& orig);

    /// \brief Destructor.
    virtual ~VarStmtAST();

    static bool classof(const ASTNode* node);

    const std::string& getName() const;
    ExprAST* getExpr() const;

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual VarStmtAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void* accept(ASTVisitor* visitor);

}; // END class VarStmtAST

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_VARSTMTAST_H
