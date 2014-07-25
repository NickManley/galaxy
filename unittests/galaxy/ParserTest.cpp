//===- unittests/galaxy/ParserTest.cpp ---------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//

#include "galaxy/Parser.h"
#include "gtest/gtest.h"
using namespace Galaxy;

namespace {

class ParserTest : public ::testing::Test {
};

TEST_F(ParserTest, PositiveNumber) {
    ExprAST *expr = Parser("24").parse();
    EXPECT_EQ("24", expr->toString());
}

TEST_F(ParserTest, NegativeNumber) {
    ExprAST *expr = Parser("-42").parse();
    EXPECT_EQ("-42", expr->toString());
}

TEST_F(ParserTest, SimpleAddition) {
    ExprAST *expr = Parser("24 + 75").parse();
    EXPECT_EQ("(+ 24 75)", expr->toString());
}

TEST_F(ParserTest, BinaryUnaryMinus) {
    ExprAST *expr = Parser("-2--3").parse();
    EXPECT_EQ("(- -2 -3)", expr->toString());
}

TEST_F(ParserTest, SimpleParenExpr) {
    ExprAST *expr = Parser("(2 + 3)").parse();
    EXPECT_EQ("(+ 2 3)", expr->toString());
}

TEST_F(ParserTest, OrderOfOperations) {
    ExprAST *expr = Parser("10+3*4/2").parse();
    EXPECT_EQ("(+ 10 (/ (* 3 4) 2))", expr->toString());
}

} // END namespace
