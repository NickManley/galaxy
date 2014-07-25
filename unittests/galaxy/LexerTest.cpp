//===- unittests/galaxy/LexerTest.cpp ----------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//

#include "galaxy/Lexer.h"
#include "gtest/gtest.h"
using namespace Galaxy;

namespace {

class LexerTest : public ::testing::Test {
};

TEST_F(LexerTest, SingleNumber) {
    Lexer lexer("24");
    Token t = lexer.consume();
    EXPECT_EQ("24", t.getValue());
    EXPECT_EQ(TokenType::NUMBER, t.getType());
}

TEST_F(LexerTest, SimpleAddition) {
    Lexer lexer("2+3");
    EXPECT_EQ("2", lexer.peek().getValue());
    EXPECT_EQ(TokenType::NUMBER, lexer.peek().getType());
    lexer.consume();
    EXPECT_EQ("+", lexer.peek().getValue());
    EXPECT_EQ(TokenType::BINOP, lexer.peek().getType());
    lexer.consume();
    EXPECT_EQ("3", lexer.peek().getValue());
    EXPECT_EQ(TokenType::NUMBER, lexer.peek().getType());
    lexer.consume();
    EXPECT_EQ(TokenType::END_FILE, lexer.peek().getType());
}

} // END namespace
