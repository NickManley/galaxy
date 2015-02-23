//===-- include/galaxy/ast/ASTNode.h - class declaration ---*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the ASTNode class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_ASTNODE_H
#define GALAXY_AST_ASTNODE_H
#include <llvm/Support/raw_ostream.h>
#include <string>

namespace Galaxy {

class ASTVisitor;

class ASTNode {
public:
    /// \see http://llvm.org/docs/HowToSetUpLLVMStyleRTTI.html
    enum class Kind {
        EXPR,
            BINARY_EXPR,
            NEGATIVE_EXPR,
            NUMBER_EXPR,
            VARIABLE_EXPR,
            EXPR_LAST, // Last
        STMT,
            VAR_STMT,
            STMT_LAST, // Last
        FUNCTION,
        PROTOTYPE,
    };
private:
    const Kind kind;
public:
    /// \brief Constructor.
    explicit ASTNode(const ASTNode::Kind& kind);

    /// \brief Copy constructor.
    ASTNode(const ASTNode& orig);

    /// \brief Destructor.
    virtual ~ASTNode();

    const ASTNode::Kind& getKind() const;

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual ASTNode* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Method to accept visitors.
    virtual void* accept(ASTVisitor* visitor);

    /// \brief Overload stream insertion operator.
    friend llvm::raw_ostream& operator<<(
        llvm::raw_ostream& out, const ASTNode& node);
}; // END class ASTNode

llvm::raw_ostream& operator<<(llvm::raw_ostream& out, const ASTNode& node);

} // END namespace Galaxy

#endif // END ifndef GALAXY_AST_ASTNODE_H
