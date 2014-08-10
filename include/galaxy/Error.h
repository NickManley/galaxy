//===-- include/galaxy/Error.h -----------------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the Error class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_ERROR_H
#define GALAXY_ERROR_H
#include <string>

namespace Galaxy {

class Error {
protected:
    std::string message;
public:
    explicit Error();
    explicit Error(const std::string& message);
    virtual ~Error();
    virtual const std::string& getMessage() const;
};

} // END namespace Galaxy

#endif // END ifndef GALAXY_ERROR_H
