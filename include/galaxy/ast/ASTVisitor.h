//===-- include/galaxy/ast/ASTVisitor.h - declaration ------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the ASTVisitor class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_ASTVISITOR_H
#define	GALAXY_AST_ASTVISITOR_H

namespace Galaxy {

class ExprAST;
class BinaryExprAST;
class NumberExprAST;

class ASTVisitor {
public:
    virtual ~ASTVisitor() { }
    virtual void visit(const ExprAST& ast) = 0;
    virtual void visit(const BinaryExprAST& ast) = 0;
    virtual void visit(const NumberExprAST& ast) = 0;

}; // END class ASTVisitor

} // END namespace Galaxy

#endif	// END ifndef GALAXY_AST_ASTVISITOR_H
