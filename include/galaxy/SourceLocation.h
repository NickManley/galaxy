//===-- include/galaxy/SourceLocation.h --------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the SourceLocation class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_SOURCELOCATION_H
#define GALAXY_SOURCELOCATION_H
#include <string>

namespace Galaxy {

class SourceLocation {
public:
    size_t line, col;
    explicit SourceLocation();
    explicit SourceLocation(size_t line, size_t col);
    SourceLocation(const SourceLocation& orig);
    std::string toString() const;
};

} // END namespace Galaxy

#endif // END ifndef GALAXY_SOURCELOCATION_H
