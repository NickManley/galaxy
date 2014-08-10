//===-- include/galaxy/Interpreter.h - Declaration ---------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the Interpreter class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_INTERPRETER_H
#define	GALAXY_INTERPRETER_H
#include "galaxy/CodeGenerator.h"
#include "galaxy/Error.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <list>
#include <string>

namespace Galaxy {

class Interpreter {
protected:
    static llvm::ExecutionEngine *engine;
    CodeGenerator codegen;
    std::list<Error*> errors;
public:
    /// \brief Constructor.
    explicit Interpreter();

    /// \brief Copy constructor.
    Interpreter(const Interpreter& orig);

    /// \brief Destructor.
    virtual ~Interpreter();

    void* interpret(const std::string& input);

    /// \brief Pop the oldest error from the errors list.
    /// \details Popping is done via FIFO (First in, First out).
    /// This way the errors are returned in the order in which
    /// they were detected.
    Error* popError();
};

} // END namespace Galaxy

#endif // END ifndef GALAXY_INTERPRETER_H
