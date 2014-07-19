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
#include <string>
#include <map>

namespace Galaxy {
    
enum class TokenType {
    EOF,        // End Of File
    EOL,        // End Of Line
    ERR,        // Error
    BINOP,      // Binary Operator
    NUMBER      // Number
};

static const std::map<const TokenType, std::string> TokenTypeStr = {
    { TokenType::EOF, "EOF" },       // End Of File
    { TokenType::EOL, "EOL" },       // End Of Line
    { TokenType::ERR, "ERR" },       // Error
    { TokenType::BINOP, "BINOP" },   // Binary Operator
    { TokenType::NUMBER, "NUMBER" }  // Number
};
    
class Token {
    
protected:
    std::string value;
    TokenType type;
    
public:
    /// \brief Construct a Token from a string.
    Token(const std::string& value, const TokenType type);
    
    /// \brief Construct a Token from a char.
    Token(const char value, const TokenType type);
    
    /// \brief Construct a Token with only the type.
    Token(const TokenType type);
    
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
    
    /// \returns true if the token matches the provided type
    /// otherwise it returns false.
    bool isType(TokenType type) const;
    
};

std::ostream& operator<<(std::ostream& out, const Token& token);
    
} // END namespace Galaxy

#endif // END ifndef TOKEN_H
