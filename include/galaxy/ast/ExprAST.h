//===-- include/galaxy/ast/ExprAST.h - class declaration ---*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the ExprAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef EXPRAST_H
#define	EXPRAST_H
#include <llvm/Support/raw_ostream.h>
#include <string>

namespace Galaxy {

class ExprAST {
public:
    /// \brief Constructor.
    ExprAST();

    /// \brief Copy constructor.
    ExprAST(const ExprAST& orig);

    /// \brief Destructor.
    virtual ~ExprAST();

    /// \brief Clone method.
    /// \details caller is responsible for calling
    /// delete on returned pointer.
    virtual ExprAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Overload stream insertion operator.
    friend llvm::raw_ostream& Galaxy::operator<<(
        llvm::raw_ostream& out, const ExprAST& expr);
}; // END class ExprAST

llvm::raw_ostream& operator<<(llvm::raw_ostream& out, const ExprAST& expr);

} // END namespace Galaxy

#endif	/* EXPRAST_H */
