//===-- tools/galaxyc/main.cpp - Definition for main -------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the main function for the
/// galaxyc tool.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/Interpreter.h"
#include "galaxy/Error.h"
#include "Shell.h"
#include <sstream>
using namespace Galaxy;

void runREPL();

int main() {
    runREPL();
    return 0;
}

void runREPL() {
    Interpreter interpreter;
    Shell& shell = Shell::getInstance();
    shell.printGraphic();
    while (true) {
        shell.printPrompt();
        std::string input = shell.readLine();
        if (input == "exit" || input == "quit") { exit(0); }
        void *result = interpreter.interpret(input);
        if (!result) {
            Error *err;
            while ((err = interpreter.popError())) {
                shell.printError(err->getMessage());
            }
            continue;
        }
        int (*FP)() = (int (*)())(intptr_t)result;
        shell.printResult(FP());
    }
}
