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
#define GALAXY_PARSER_H
#include "galaxy/ast/BinaryExprAST.h"
#include "galaxy/ast/NegativeExprAST.h"
#include "galaxy/ast/NumberExprAST.h"
#include "galaxy/ParseError.h"
#include <list>

namespace Galaxy {

class Lexer;
class Token;

class Parser {
protected:
    Lexer *lexer;
    std::list<ParseError*> errors;
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
    ExprAST* parseNumberExpr();

    /// \brief Parse negative number expression.
    ExprAST* parseNegativeExpr();

    /// \brief Parse term.
    ExprAST* parseTerm();

    /// \brief Parse binary expression.
    ExprAST* parseBinaryExpr(int prec, ExprAST *lhs);

    bool hasErrors();

    /// \brief Pop the oldest error from the errors list.
    /// \details Popping is done via FIFO (First in, First out).
    /// This way the errors are returned in the order in which
    /// they were detected.
    ParseError* popError();

protected:

    /// \brief Performs a deep copy on the list of errors.
    static std::list<ParseError*> copyErrors(std::list<ParseError*> errors);

    /// \name utility methods
    /// @{
    static bool isEndOfExpr(const Token& t);
    static bool isBinOp(const Token& t);
    /// @}
}; // END class Parser

} // END namespace Galaxy

#endif // END ifndef GALAXY_PARSER_H
