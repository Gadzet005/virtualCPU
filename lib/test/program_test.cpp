#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include "parser.hpp"
#include "processor.hpp"

using namespace vm;
using namespace std;

TEST(Programs, factorial) {
    using TestCase = tuple<int, int>;
    const vector<TestCase> cases = {
        {0, 1}, {1, 1}, {2, 2}, {3, 6}, {4, 24},
        {5, 120}, {6, 720}, {7, 5040}, {8, 40320}, {9, 362880},
        {10, 3628800}, {11, 39916800}, {12, 479001600}
    };

    stringstream input, output;
    Processor processor(input, output);
    Program program1 = Parser::parseProgram("../data/programs/fact.txt");
    Program program2 = Parser::parseProgram("../data/programs/rec_fact.txt");

    auto startTestCase = [&input, &output, &processor](int n) { 
        input << n << endl; output.str(string()); processor.clear(); 
    };

    for (const auto& [n, expected] : cases) {
        startTestCase(n);
        processor.executeProgram(program1);
        EXPECT_EQ(output.str(), to_string(expected) + "\n");

        startTestCase(n);
        processor.executeProgram(program2);
        EXPECT_EQ(output.str(), to_string(expected) + "\n");
    }
}

TEST(Programs, fibonacci40) {
    stringstream input, output;
    Processor processor(input, output);
    Program program = Parser::parseProgram("../data/programs/fib40.txt");
    processor.executeProgram(program);

    int n;
    output >> n;
    EXPECT_EQ(n, 1);
    output >> n;
    EXPECT_EQ(n, 1);

    int a = 1, b = 1;
    for (int i = 2; i < 40; i++) {
        int tmp = a + b;
        b = a;
        a = tmp;

        output >> n;
        EXPECT_EQ(n, a);
    }
}

TEST(Programs, discriminant) {
    // a, b, c, D
    using TestCase = tuple<int, int, int, int>;
    const vector<TestCase> cases = {
        {0, 0, 0, 0}, {5, 8, 6, -1}, {5, 13, 6, 49}, {8, 16, 8, 0},
        {1, 1, 1, -1}, {9, -20, 8, 112}, {10, 20, -8, 720}, {-1, -1, 1, 5}
    };

    stringstream input, output;
    Processor processor(input, output);
    Program program = Parser::parseProgram("../data/programs/discr.txt");
    
    auto startTestCase = [&input, &output, &processor](int a, int b, int c) { 
        input << a << " " << b << " " << c << endl; 
        output.str(string()); processor.clear(); 
    };

    for (const auto& [a, b, c, expected] : cases) {
        startTestCase(a, b, c);
        processor.executeProgram(program);
        EXPECT_EQ(output.str(), to_string(expected) + "\n");
    }

}
