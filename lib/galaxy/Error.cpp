//===-- lib/galaxy/Error.cpp -------------------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the Error class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/Error.h"
using namespace Galaxy;

Error::Error() { }

Error::Error(const std::string& message) : message(message) { }

Error::~Error() { }

Error* Error::clone() const {
    return new Error(*this);
}

const std::string& Error::getMessage() const {
    return message;
}
