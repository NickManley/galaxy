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

#ifndef BINARYEXPRAST_H
#define	BINARYEXPRAST_H
#include "ExprAST.h"

namespace Galaxy {

class BinaryExprAST : public ExprAST {
protected:
    const std::string op;
    const ExprAST *lhs, *rhs;

public:
    /// \brief Constructor.
    BinaryExprAST(const std::string op, ExprAST *lhs, ExprAST *rhs);

    /// \brief Copy constructor.
    BinaryExprAST(const BinaryExprAST& orig);

    /// \brief Destructor.
    virtual ~BinaryExprAST();

    /// \brief Convert to std::string.
    virtual std::string toString() const;
    
    /// \brief Convert to LLVM IR code.
    virtual llvm::Value* toCode() const;
}; // END class BinaryExprAST

} // END namespace Galaxy

#endif	/* BINARYEXPRAST_H */