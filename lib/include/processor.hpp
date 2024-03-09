#pragma once
#include <iostream>
#include "stack.hpp"
#include "program.hpp"

namespace vm {

class Processor {
public:
    Stack<int> stack;
    std::istream& in = std::cin;
    std::ostream& out = std::cout;

    void executeProgram(Program& program);
};

}
