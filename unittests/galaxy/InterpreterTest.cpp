//===- unittests/galaxy/InterpreterTest.cpp ----------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//

#include "galaxy/Interpreter.h"
#include "gtest/gtest.h"
using namespace Galaxy;

namespace {

class InterpreterTest : public ::testing::Test {
protected:
    Interpreter interpreter;
};

TEST_F(InterpreterTest, SingleNumber) {
    void *result = interpreter.interpret("129");
    int (*FP)() = (int (*)())(intptr_t)result;
    EXPECT_EQ(129, FP());
}

TEST_F(InterpreterTest, SimpleExpr) {
    void *result = interpreter.interpret("91-(-8+2)*10");
    int (*FP)() = (int (*)())(intptr_t)result;
    EXPECT_EQ(151, FP());
}

} // END namespace
