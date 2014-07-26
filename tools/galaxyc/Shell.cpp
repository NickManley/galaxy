//===-- tools/galaxyc/Shell.cpp - Definition for Shell -----*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the Shell class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "Shell.h"
#include "galaxy/Parser.h"
#include <cstdio>
using namespace Galaxy;

Shell::Shell() { }

Shell& Shell::getInstance() {
    static Shell instance;
    return instance;
}

std::string Shell::readLine() {
    static const size_t INIT_BUF_LEN = 128;
    std::string line;
    line.reserve(INIT_BUF_LEN);
    while (true) {
        int c = getchar();
        switch (c) {
            case '\r':
            case '\n':
            case '\0':
            case EOF: return line;
            default: break;
        }
        char ch = (char)c;
        line.append(&ch, 1);
    }
    return line;
}

std::string Shell::parse(const std::string& input) {
    if (input == "exit" || input == "quit") { exit(0); }
    std::string s;
    llvm::raw_string_ostream rso(s);
    Parser(input).parse()->toCode()->print(rso);
    return rso.str();
}

void Shell::printResult(const std::string& result) {
    llvm::outs().changeColor(llvm::outs().CYAN, true);
    llvm::outs() << result.substr(3) << "\n";
    llvm::outs().flush();
}

void Shell::printPrompt(const std::string& prefix) {
    llvm::outs().changeColor(llvm::outs().WHITE, true);
    llvm::outs() << prefix;
    llvm::outs().flush();
}

void Shell::printGraphic() {
    llvm::outs().changeColor(llvm::raw_ostream::Colors::YELLOW, true);
    llvm::outs() <<
        "        ___          _          _        "
        "     _          _  _      _  _ \n"
        "      ,\"___\".       /.\\        FJ     "
        "       /.\\        FJ  LJ    FJ  LJ\n"
        "      FJ---L]      //_\\\\      J |      "
        "     //_\\\\       J \\/ F    J \\/ F\n"
        "     J |  [\"\"L    / ___ \\     | |     "
        "     / ___ \\      /    \\    J\\  /L\n"
        "     | \\___] |   / L___J \\    F L_____ "
        "   / L___J \\    /  /\\  \\    F  J\n"
        "     J\\_____/F  J__L   J__L  J________L "
        " J__L   J__L  J__//\\\\__L  |____|\n"
        "      J_____F   |__L   J__|  |________|  "
        "|__L   J__|  |__/  \\__|  |____|\n"
        "\n\n"
        "                        "
        "The Galaxy Programming Language\n\n";
    llvm::outs().changeColor(llvm::raw_ostream::Colors::YELLOW, false);
    llvm::outs() <<
        "                             "
        "Version: 0.1.0-dev\n"
        "                            "
        "Author: Nick Manley\n\n";
    llvm::outs().flush();
}
