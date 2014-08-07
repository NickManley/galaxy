//===-- include/galaxy/ast/FunctionAST.h -------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the FunctionAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_FUNCTIONAST_H
#define	GALAXY_AST_FUNCTIONAST_H
#include "galaxy/ast/ExprAST.h"
#include "galaxy/ast/PrototypeAST.h"

namespace Galaxy {

class FunctionAST {
protected:
    PrototypeAST *prototype;
    ExprAST *expr;
public:
    /// \brief Constructor.
    FunctionAST();

    /// \brief Copy constructor.
    FunctionAST(const FunctionAST& orig);

    /// \brief Destructor.
    virtual ~FunctionAST();

    /// \brief Clone method.
    virtual FunctionAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Overload stream insertion operator.
    friend llvm::raw_ostream& Galaxy::operator<<(
            llvm::raw_ostream& out, const FunctionAST& func);
}; // END class FunctionAST

llvm::raw_ostream& operator<<(llvm::raw_ostream& out,
        const FunctionAST& func);

} // END namespace Galaxy

#endif	// END ifndef GALAXY_AST_FUNCTIONAST_H
