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

#include "galaxy/Token.h"
#include <iostream>
using namespace Galaxy;

int main() {
    Token t("0", TokenType::NUMBER);
    std::cout << t << std::endl;
    return 0;
}
