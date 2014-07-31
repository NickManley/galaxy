//===-- include/galaxy/Result.h ----------------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_RESULT_H
#define	GALAXY_RESULT_H
#include "Error.h"
#include <llvm/Support/Casting.h>
#include <cassert>
#include <type_traits>

namespace Galaxy {

/// \brief Stores a return value along with a possible Error object.
/// \details The motivation behind this class is to be able to
/// return more than just error codes. Although C++ provides
/// std::error_code, it has a disadvantage. The associated
/// std::error_category can only provide a predetermined message.
/// Therefore, if one wants to return an error message such as,
/// "Invalid input X" where X is some variable, then this cannot
/// be achieved with std::error_category which only allows
/// constant strings to be returned as error messages. This is
/// also very limiting in scenarios where one wishes to return
/// more diagnostic information about the nature of the error.
/// This class requires that V either be a primitive, a pointer,
/// or have a zero argument constructor. This is because when a
/// value/error is provided, Result must construct both,
/// even though only one will ever be returned.
/// It is required that E inherit from the Galaxy::Error class.
/// If V or E are pointers, Result will NOT free their memory.
/// It does not consider itself the owner of the memory.
template<class V, class E>
class Result {
protected:
    bool hasError;
    const V value;
    const E error;
public:
    Result(const V& val) : hasError(false), value(val), error(E()) {
        assert(llvm::isa<Galaxy::Error>(error) &&
                "Result<V,E> : E is not an Error type.");
    }

    Result(const E& err) : hasError(true), value(V()), error(err) {
        assert(llvm::isa<Galaxy::Error>(error) &&
                "Result<V,E> : E is not an Error type.");
    }

    const V& val() const {
        assert(!hasError && "Cannot call val() on Result with error.");
        return value;
    }

    const E& err() const {
        assert(hasError && "Cannot call err() on Result with value.");
        return error;
    }

    operator bool() const {
        return !hasError;
    }

    bool operator!() const {
        return hasError;
    }

    const V& operator*() const {
        assert(!hasError && "Cannot access value on Result with error.");
        return value;
    }
    
    template<class T = V>
    typename std::enable_if<std::is_pointer<T>::value, T>::type
    operator->() const {
        assert(!hasError && "Cannot access value on Result with error.");
        return value;
    }
    
    template<class T = V>
    typename std::enable_if<std::is_same<
        typename std::remove_pointer<T>::type, T>::value, const T*>::type
    operator->() const {
        assert(!hasError && "Cannot access value on Result with error.");
        return &value;
    }
}; // END class Result

} // END namespace Galaxy

#endif // END ifndef GALAXY_RESULT_H
