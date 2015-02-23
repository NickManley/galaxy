//===-- lib/galaxy/ast/PrototypeAST.cpp - Definition -------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definition of the PrototypeAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#include "galaxy/ast/ASTVisitor.h"
#include "galaxy/ast/PrototypeAST.h"
using namespace Galaxy;

PrototypeAST::PrototypeAST() { }

PrototypeAST::PrototypeAST(const std::string& name,
        const std::vector<std::string>& args) : name(name), args(args) { }

PrototypeAST::PrototypeAST(const PrototypeAST& orig)
        : name(orig.name), args(orig.args) { }

PrototypeAST::~PrototypeAST() { }

const std::string& PrototypeAST::getName() const {
    return name;
}

const std::string& PrototypeAST::getArg(size_t index) const {
    return args.at(index);
}

const std::vector<std::string>& PrototypeAST::getArgs() const {
    return args;
}

PrototypeAST* PrototypeAST::clone() const {
    return new PrototypeAST(*this);
}

std::string PrototypeAST::toString() const {
    std::string s;
    llvm::raw_string_ostream rso(s);
    rso << "func " << name << "(";
    for (auto it = args.begin(); it != args.end(); ++it) {
        rso << *it;
        if (it+1 != args.end()) {
            rso << ", ";
        }
    }
    rso << ")";
    return rso.str();
}

void* PrototypeAST::accept(ASTVisitor* visitor) {
    return visitor->visit(*this);
}

llvm::raw_ostream& Galaxy::operator<<(llvm::raw_ostream& out,
        const PrototypeAST& proto) {
    return out << proto.toString();
}
