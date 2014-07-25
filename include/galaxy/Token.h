//===-- Token.h - Token class declaration ------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the Token class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef TOKEN_H
#define	TOKEN_H
#include <llvm/Support/raw_ostream.h>
#include <map>
#include <string>

namespace Galaxy {
    
enum class TokenType {
    END_FILE,   // End File
    END_LINE,   // End Line
    ERR,        // Error
    BINOP,      // Binary Operator
    NUMBER,     // Number
    PAREN       // Parenthesis
};

static const std::map<const TokenType, const std::string> TokenTypeStr = {
    { TokenType::END_FILE, "END_FILE" },  // End File
    { TokenType::END_LINE, "END_LINE" },  // End Line
    { TokenType::ERR, "ERR" },       // Error
    { TokenType::BINOP, "BINOP" },   // Binary Operator
    { TokenType::NUMBER, "NUMBER" }, // Number
    { TokenType::PAREN, "PAREN" }    // Parenthesis
};

static const std::map<const std::string, int> Precedence = {
    { "+", 10 },
    { "-", 10 },
    { "*", 20 },
    { "/", 20 }
};

class Token {
    
protected:
    std::string value;
    TokenType type;
    
public:
    /// \brief Construct a Token from a string.
    explicit Token(const std::string& value, const TokenType type);
    
    /// \brief Construct a Token from a char.
    explicit Token(const char value, const TokenType type);
    
    /// \brief Construct a Token with only the type.
    explicit Token(const TokenType type);
    
    /// \brief Copy constructor.
    /// \param[in] orig Original Token.
    Token(const Token& orig);
    
    /// \brief Destructor.
    virtual ~Token();
    
    /// \brief Assignment operator.
    /// \param[in] orig Original value.
    /// \returns copy of the object.
    Token& operator=(const Token& orig);
    
    /// \brief Overload stream insertion operator.
    friend llvm::raw_ostream& Galaxy::operator<<(
        llvm::raw_ostream& out, const Token& token);
    
    /// \returns the string value of the token.
    const std::string& getValue() const;
    
    /// \returns the TokenType of the token.
    const TokenType& getType() const;

    /// \returns the precedence of the token.
    int getPrec() const;
};

llvm::raw_ostream& operator<<(llvm::raw_ostream& out, const Token& token);
    
} // END namespace Galaxy

#endif // END ifndef TOKEN_H
