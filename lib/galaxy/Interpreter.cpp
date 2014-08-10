//===-- lib/galaxy/Interpreter.cpp - Definition ------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the Interpreter class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ExprAST.h"
#include "galaxy/ast/FunctionAST.h"
#include "galaxy/Interpreter.h"
#include "galaxy/Parser.h"
#include <llvm/Support/TargetSelect.h>
using namespace Galaxy;

llvm::ExecutionEngine* Interpreter::engine = NULL;

Interpreter::Interpreter() {
    if (engine) { return; }
    llvm::InitializeNativeTarget();
    std::string engineErr;
    engine = llvm::EngineBuilder(codegen.module)
            .setErrorStr(&engineErr)
            .create();
    if (!engine) {
        llvm::outs() << "[Error] Could not create ExecutionEngine: "
                << engineErr << "\n";
        llvm::outs().flush();
        exit(1);
    }
}

Interpreter::Interpreter(const Interpreter& orig)
        : codegen(orig.codegen), errors(orig.errors) { }

Interpreter::~Interpreter() {
    for(auto e : errors) {
        delete e;
    }
    errors.clear();
}

void* Interpreter::interpret(const std::string& input) {
    // Parse input
    Parser parser(input);
    ExprAST *parseTree = parser.parse();
    if (!parseTree) {
        ParseError *err;
        while ((err = parser.popError())) {
            errors.push_back(err);
        }
        return NULL;
    }
    // Generate code
    llvm::Function *func = codegen.getFunction(parseTree);
    delete parseTree;
    return engine->getPointerToFunction(func);
}

Error* Interpreter::popError() {
    if (errors.size() > 0) {
        auto e = errors.front();
        errors.pop_front();
        return e;
    }
    return NULL;
}
