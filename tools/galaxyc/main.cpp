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

#include "galaxy/ast/FunctionAST.h"
#include "galaxy/ast/PrototypeAST.h"
#include "galaxy/CodeGenerator.h"
#include "galaxy/Parser.h"
#include "Shell.h"
using namespace Galaxy;

void printValue(ExprAST *expr);
void printFunc(ExprAST *expr);

int main() {
    CodeGenerator codegen;
    Shell& shell = Shell::getInstance();
    shell.printGraphic();
    while (true) {
        shell.printPrompt();
        std::string input = shell.readLine();
        if (input == "exit" || input == "quit") { exit(0); }
        std::string output;
        llvm::raw_string_ostream rso(output);
        Parser parser(input);
        ExprAST *parseTree = parser.parse();
        if (!parseTree) {
            ParseError *err;
            while ((err = parser.popError())) {
                rso << err->getMessage() << "\n";
            }
            shell.printError(rso.str());
            continue;
        }
        printFunc(parseTree);
        delete parseTree;
    }
    return 0;
}

void printValue(ExprAST *expr) {
    Shell& shell = Shell::getInstance();
    CodeGenerator codegen;
    std::string output;
    llvm::raw_string_ostream rso(output);

    codegen.getValue(expr)->print(rso);
    shell.printResult(rso.str().substr(3));
}

void printFunc(ExprAST *expr) {
    Shell& shell = Shell::getInstance();
    CodeGenerator codegen;
    std::string output;
    llvm::raw_string_ostream rso(output);
    FunctionAST *func = new FunctionAST(new PrototypeAST(), expr);

    codegen.getFunction(func)->print(rso);
    shell.printResult(rso.str());
    delete func;
}
