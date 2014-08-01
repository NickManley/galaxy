//===- unittests/galaxy/ResultTest.cpp ---------------------*- C++ -*-===//
//
//                     The Galaxy Programming Language
//
// This file is distributed under the ISC License.
// See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------===//

#include "galaxy/Error.h"
#include "galaxy/Result.h"
#include "gtest/gtest.h"
using namespace Galaxy;

namespace {

const std::string MESSAGE = "Example Error Message.";

class ExampleObject {
private:
    int data;
public:
    ExampleObject() { }
    ExampleObject(int data) : data(data) { }
    int getData() { return data; }
    void setData(int data) { this->data = data; }
};

class ExampleError : public Error {
private:
    std::string msg;
public:
    ExampleError() { }
    ExampleError(const std::string& msg) : msg(msg) { }
    const std::string& getMessage() { return msg; }
};

class ResultTest : public ::testing::Test {
protected:
    static Result<ExampleObject, ExampleError> getTestValue() {
        return ExampleObject(2014);
    }

    static Result<ExampleObject, ExampleError> getTestError() {
        return ExampleError(MESSAGE);
    }

    static Result<ExampleObject*, ExampleError> getTestValuePointer() {
        return new ExampleObject(2014);
    }

    static Result<ExampleObject*, ExampleError> getTestErrorPointer() {
        return ExampleError(MESSAGE);
    }
};

TEST_F(ResultTest, UsingValue) {
    auto v = getTestValue();
    EXPECT_TRUE(bool(v));
    EXPECT_FALSE(!v);
    EXPECT_EQ(2014, v->getData());
    EXPECT_EQ(2014, (*v).getData());

    auto e = getTestError();
    EXPECT_FALSE(bool(e));
    EXPECT_TRUE(!e);
    EXPECT_EQ(MESSAGE, e.err().getMessage());
}

TEST_F(ResultTest, UsingPointer) {
    auto v = getTestValuePointer();
    EXPECT_TRUE(bool(v));
    EXPECT_FALSE(!v);
    EXPECT_EQ(2014, v->getData());
    EXPECT_EQ(2014, (*v)->getData());
    delete *v;

    auto e = getTestErrorPointer();
    EXPECT_FALSE(bool(e));
    EXPECT_TRUE(!e);
    EXPECT_EQ(MESSAGE, e.err().getMessage());
}

} // END namespace
