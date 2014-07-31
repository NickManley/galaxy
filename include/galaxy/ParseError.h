//===-- include/galaxy/ParseError.h -------------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the ParseError class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_PARSEERROR_H
#define	GALAXY_PARSEERROR_H
#include "Error.h"
#include <string>

namespace Galaxy {
    
enum class ParseErrorType {
    UNEXPECTED_TOKEN
};
    
class ParseError : public Error {
protected:
    ParseErrorType type;
    std::string message;
public:
    explicit ParseError();
    explicit ParseError(const ParseErrorType& type);
    explicit ParseError(const ParseErrorType& type,
    const std::string& message);
    virtual ~ParseError();
    const std::string& getMessage() const;
    const ParseErrorType& getType() const;
};

} // END namespace Galaxy

#endif // END ifndef GALAXY_PARSEERROR_H