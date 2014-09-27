//===-- include/galaxy/CodeGenError.h ----------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the CodeGenError class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_CODEGENERROR_H
#define GALAXY_CODEGENERROR_H
#include "Error.h"
#include <string>

namespace Galaxy {

enum class CodeGenErrorType {
    UNKNOWN,
    UNDEFINED_VARIABLE,
    EXPECTED_IDENT_LHS
};

class CodeGenError : public Error {
protected:
    CodeGenErrorType type;
public:
    explicit CodeGenError();
    explicit CodeGenError(const CodeGenErrorType& type);
    explicit CodeGenError(const CodeGenErrorType& type,
    const std::string& message);
    virtual ~CodeGenError();
    virtual const std::string& getMessage() const;
    const CodeGenErrorType& getType() const;
};

} // END namespace Galaxy

#endif // END ifndef GALAXY_CODEGENERROR_H
