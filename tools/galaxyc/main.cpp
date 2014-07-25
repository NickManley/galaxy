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

#include "galaxy/Parser.h"
#include <iostream>
using namespace Galaxy;

int main() {
    std::string input;
    while (true) {
        llvm::outs() << "> ";
        llvm::outs().flush();
        std::getline(std::cin, input);
        if (input == "exit") { break; }
        llvm::outs() << Parser(input).parse()->toString() << "\n";
    }
    return 0;
}
