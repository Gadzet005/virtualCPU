#include <gtest/gtest.h>
#include <string>
#include "stack.hpp"

using namespace vm;
using std::string;

TEST(StackTest, PushPop) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    for (int i = 3; !stack.empty(); i--) {
        EXPECT_EQ(stack.getSize(), i);
        EXPECT_EQ(stack.top(), i);
        stack.pop();
    }

    EXPECT_THROW(stack.top(), EmptyStackError);
    EXPECT_THROW(stack.pop(), EmptyStackError);
    EXPECT_EQ(stack.getSize(), 0);
    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, withString) {
    Stack<string> s;
    string str = "???";

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.getSize(), 0);
    EXPECT_THROW(s.top(), EmptyStackError);
    EXPECT_THROW(s.pop(), EmptyStackError);

    s.push("hello world!");
    EXPECT_EQ(s.top(), "hello world!");

    s.push(str);
    EXPECT_EQ(s.top(), "???");
    str += "hi";
    EXPECT_EQ(s.top(), "???");

    s.push(std::move(str));
    string& strRef = s.top();
    strRef += "...";
    EXPECT_EQ(s.top(), "???hi...");

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.getSize(), 0);
}

TEST(StackTest, copy) {
    Stack<size_t> s1;
    for (int i = 0; i < 10; i++) {
        s1.push(i);
    }

    Stack<size_t> s2(s1);
    EXPECT_EQ(s2.getSize(), 10);
    int i = 9;
    while (!s2.empty()) {
        EXPECT_EQ(s2.top(), i);
        s2.pop();
        i--;
    }

    Stack<size_t> s3(std::move(s2));
    EXPECT_EQ(s3.getSize(), 0);

    s3 = s1;
    EXPECT_EQ(s3.getSize(), 10);

    s3.pop();
    s1 = std::move(s3);
    s3.clear();

    s1 = s1;
    s1 = std::move(s1);

    EXPECT_EQ(s1.getSize(), 9);
    EXPECT_EQ(s1.top(), 8);

    Stack<size_t> s4 = Stack<size_t>();
    for (int i = 0; i < 100; i++) {
        s4.push(i);
    }

    EXPECT_EQ(s4.getSize(), 100);
    s4 = s1;
    EXPECT_EQ(s4.getSize(), 9);
}