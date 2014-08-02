//===-- lib/galaxy/SourceLocation.cpp ----------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the SourceLocation class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/SourceLocation.h"
#include <llvm/Support/raw_ostream.h>
using namespace Galaxy;

SourceLocation::SourceLocation() : line(0), col(0) { }

SourceLocation::SourceLocation(size_t line, size_t col)
        : line(line), col(col) { }

std::string SourceLocation::toString() const {
    std::string s;
    llvm::raw_string_ostream rso(s);
    rso << line << ':' << col;
    return rso.str();
}
