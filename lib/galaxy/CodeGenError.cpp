//===-- lib/galaxy/CodeGenError.cpp ------------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the CodeGenError class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/CodeGenError.h"
using namespace Galaxy;

CodeGenError::CodeGenError(const CodeGenErrorType& type)
        : type(type) { }

CodeGenError::CodeGenError(const CodeGenErrorType& type,
        const std::string& message)
        : Error(message), type(type) { }

CodeGenError::~CodeGenError() { }

const std::string& CodeGenError::getMessage() const {
    return message;
}

const CodeGenErrorType& CodeGenError::getType() const {
    return type;
}
