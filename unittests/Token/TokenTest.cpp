//===- unittests/Token/TokenTest.cpp -----------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//

#include "galaxy/Token.h"
#include "gtest/gtest.h"

using namespace Galaxy;

namespace {

class TokenTest : public ::testing::Test {
};


TEST_F(TokenTest, Basics) {
  Token t("0", TokenType::NUMBER);
  EXPECT_EQ("0", t.getValue());
}

} // END namespace
