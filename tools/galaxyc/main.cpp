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

#include "galaxy/Lexer.h"
#include <iostream>
using namespace Galaxy;

int main() {
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit") { break; }
        Lexer lexer(input);
        while (lexer.peek().getType() != TokenType::EOF) {
            Token t = lexer.consume();
            std::cout << t << std::endl;
            if (t.getType() == TokenType::ERR) { break; }
        }
    }
    return 0;
}
