//===-- lib/galaxy/ParseError.cpp --------------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the ParseError class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ParseError.h"
using namespace Galaxy;

ParseError::ParseError() { }

ParseError::ParseError(const ParseErrorType& type)
        : type(type) { }

ParseError::ParseError(const ParseErrorType& type,
        const std::string& message)
        : Error(message), type(type) { }

ParseError::~ParseError() { }

Error* ParseError::clone() const {
    return new ParseError(*this);
}

const std::string& ParseError::getMessage() const {
    return message;
}

const ParseErrorType& ParseError::getType() const {
    return type;
}
