//===-- include/galaxy/Lexer.h - Lexer class declaration ---*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the Lexer class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_LEXER_H
#define GALAXY_LEXER_H
#include "galaxy/SourceLocation.h"
#include "galaxy/Token.h"

namespace Galaxy {

class Lexer {

protected:
    // The Galaxy source code to lex.
    const std::string src;

    // The length of src.
    const std::size_t len;

    // The current index of where the lexer is.
    // It can never be >= len.
    std::size_t idx;

    // The source location is similar to idx but
    // tracks newlines and columns.
    SourceLocation loc;
public:
    /// \brief Construct a Lexer from a string.
    explicit Lexer(const std::string& input);

    /// \brief Copy constructor.
    /// \param[in] orig Original Lexer.
    Lexer(const Lexer& orig);

    /// \brief Destructor.
    virtual ~Lexer();

    Token consume();
    Token peek();
    Token peekAhead();
    const SourceLocation location();
protected:
    Token lexToken();
    Token lexBinOp();
    Token lexNumber();
    Token lexIdentOrKeyword();

    /// \name string utility methods
    /// @{
    static bool isAlpha(char c);
    static bool isDigit(char c);
    static bool isAlphaOrDigit(char c);
    static bool isBinOp(char c);
    static bool isWhitespace(char c);
    static bool isParen(char c);
    /// @}

}; // END class Lexer

} // END namespace Galaxy

#endif // END ifndef GALAXY_LEXER_H
