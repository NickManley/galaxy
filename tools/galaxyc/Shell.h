//===-- tools/galaxyc/Shell.h - Declaration for Shell ------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the Shell class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef SHELL_H
#define	SHELL_H
#include <llvm/Support/raw_ostream.h>
#include <string>

namespace Galaxy {

/// \brief The Shell class is used for the REPL.
/// \details This class is a singleton.
class Shell
{
private:
    Shell(); // Implement as empty
    Shell(Shell const&); // Don't Implement
    void operator=(Shell const&); // Don't implement
public:
    static Shell& getInstance();
    std::string readLine();
    std::string parse(const std::string& input);
    void printResult(const std::string& result);
    void printPrompt(const std::string& prefix = ">>> ");
    void printGraphic();
}; // END class Shell

} // END namespace Galaxy

#endif	/* SHELL_H */
