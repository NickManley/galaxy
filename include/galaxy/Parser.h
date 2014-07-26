//===-- include/galaxy/Parser.h - class declaration --------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the Parser class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_PARSER_H
#define	GALAXY_PARSER_H
#include "ast/BinaryExprAST.h"
#include "ast/NumberExprAST.h"
#include "Lexer.h"

namespace Galaxy {

class Parser {
protected:
    Lexer* lexer;
public:
    /// \brief Constructor.
    explicit Parser(const std::string& src);

    /// \brief Copy constructor.
    Parser(const Parser& orig);

    /// \brief Destructor.
    virtual ~Parser();

    /// \brief Parse source.
    /// \details The caller is responsible for calling
    /// delete on the returned pointer.
    /// \returns ExprAST pointer.
    ExprAST* parse();

    /// \brief Parse expression.
    ExprAST* parseExpr();

    /// \brief Parse number expression.
    NumberExprAST* parseNumberExpr();

    /// \brief Parse negative number expression.
    NumberExprAST* parseNegativeExpr();

    /// \brief Parse term.
    ExprAST* parseTerm();

    /// \brief Parse binary expression.
    ExprAST* parseBinaryExpr(int prec, ExprAST *lhs);
}; // END class Parser

} // END namespace Galaxy

#endif // END ifndef GALAXY_PARSER_H
