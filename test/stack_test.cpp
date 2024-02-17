#include <gtest/gtest.h>
#include <string>
#include "stack.hpp"

using namespace vm;
using std::string;

TEST(Stack, withInt) {
    Stack s;

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.getSize(), 0);
    EXPECT_THROW(s.top(), std::runtime_error);
    
    for (int i = 0; i < 20; i++) {
        s.push(5);
        EXPECT_EQ(s.top(), 5);
        s.push(i);
        EXPECT_EQ(s.top(), i);
    }  

    EXPECT_EQ(s.getSize(), 40);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.top(), 19);

    s.pop();
    EXPECT_EQ(s.top(), 5);
    EXPECT_EQ(s.getSize(), 39);

    while (!s.empty()) {
        s.pop();
    }

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.getSize(), 0);
}

TEST(Stack, withString) {
    Stack<string> s;
    string str = "???";

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.getSize(), 0);
    EXPECT_THROW(s.top(), std::runtime_error);

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

TEST(Stack, copy) {
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