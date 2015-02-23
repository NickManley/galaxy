//===-- include/galaxy/ast/StmtAST.h - class declaration ---*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the StmtAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_STMTAST_H
#define GALAXY_AST_STMTAST_H
#include "ASTNode.h"

namespace Galaxy {

class StmtAST : public ASTNode {
public:
    /// \brief Constructor.
    explicit StmtAST();

    /// \brief Constructor with KIND.
    explicit StmtAST(const ASTNode::Kind& kind);

    /// \brief Copy constructor.
    StmtAST(const StmtAST& orig);

    /// \brief Destructor.
    virtual ~StmtAST();

    static bool classof(const ASTNode* node);

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual StmtAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void* accept(ASTVisitor* visitor);

}; // END class StmtAST

llvm::raw_ostream& operator<<(llvm::raw_ostream& out, const StmtAST& stmt);

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_STMTAST_H
