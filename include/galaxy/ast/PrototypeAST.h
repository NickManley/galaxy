//===-- include/galaxy/ast/PrototypeAST.h ------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the PrototypeAST class.
/// \author Nicholas E. Manley
/// \copyright ISC License
///
//===-----------------------------------------------------------------===//

#ifndef GALAXY_AST_PROTOTYPEAST_H
#define	GALAXY_AST_PROTOTYPEAST_H
#include <llvm/Support/raw_ostream.h>
#include <string>
#include <vector>

namespace Galaxy {

class PrototypeAST {
protected:
    std::string name;
    std::vector<std::string> args;
public:
    /// \brief Constructor.
    PrototypeAST();
    
    /// \brief Constructor.
    PrototypeAST(const std::string& name,
            const std::vector<std::string>& args);

    /// \brief Copy constructor.
    PrototypeAST(const PrototypeAST& orig);

    /// \brief Destructor.
    virtual ~PrototypeAST();

    const std::string& getName() const;
    const std::string& getArg(size_t index) const;
    const std::vector<std::string>& getArgs() const;

    /// \brief Clone method.
    virtual PrototypeAST* clone() const;

    /// \brief Convert to std::string.
    virtual std::string toString() const;

    /// \brief Convert PrototypeAST to LLVM IR.
    virtual llvm::Function* toCode() const;

    /// \brief Overload stream insertion operator.
    friend llvm::raw_ostream& Galaxy::operator<<(
            llvm::raw_ostream& out, const PrototypeAST& proto);
}; // END class PrototypeAST

llvm::raw_ostream& operator<<(llvm::raw_ostream& out,
        const PrototypeAST& proto);

} // END namespace Galaxy

#endif	// END ifndef GALAXY_AST_PROTOTYPEAST_H
