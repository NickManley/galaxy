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
#include <map>
#include <string>

namespace Galaxy {
    
enum class TokenType {
    EOF,        // End Of File
    EOL,        // End Of Line
    ERR,        // Error
    BINOP,      // Binary Operator
    NUMBER      // Number
};

static const std::map<const TokenType, const std::string> TokenTypeStr = {
    { TokenType::EOF, "EOF" },       // End Of File
    { TokenType::EOL, "EOL" },       // End Of Line
    { TokenType::ERR, "ERR" },       // Error
    { TokenType::BINOP, "BINOP" },   // Binary Operator
    { TokenType::NUMBER, "NUMBER" }  // Number
};
    
class Token {
    
protected:
    const std::string value;
    const TokenType type;
    
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
    
    /// \brief Assignment operator.
    /// \param[in] orig Original value.
    /// \returns copy of the object.
    Token& operator=(const Token& orig);
    
    /// \brief Destructor.
    virtual ~Token();
    
    /// \brief Overload stream insertion operator.
    friend std::ostream& Galaxy::operator<<(
        std::ostream& out, const Token& token);
    
    /// \returns the string value of the token.
    const std::string& getValue() const;
    
    /// \returns the TokenType of the token.
    const TokenType& getType() const;
    
};

std::ostream& operator<<(std::ostream& out, const Token& token);
    
} // END namespace Galaxy

#endif // END ifndef TOKEN_H
