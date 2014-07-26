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

#include "shell.h"
using namespace Galaxy;

int main() {
    Shell& shell = Shell::getInstance();
    shell.printGraphic();
    while (true) {
        shell.printPrompt();
        shell.printResult( shell.parse( shell.readLine() ) );
    }
    return 0;
}
