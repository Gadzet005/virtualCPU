#pragma once
#include <iostream>
#include <map>
#include "stack.hpp"
#include "program.hpp"

namespace vm {

class Processor {
public:
    Processor() = default;
    Processor(std::istream& input, std::ostream& output) : 
        in(input), out(output) {};

    std::istream& getInput() { return in; }
    std::ostream& getOutput() { return out; }
    Stack<int>& getStack() { return stack; }

    void setRegister(const std::string& name, int value) { registers[name] = value; }
    int getRegister(const std::string& name) const { return registers.at(name); }

    void executeProgram(Program& program);
    Program& getCurProgram() { return *curProgram; }

private:
    Stack<int> stack;
    std::map<std::string, int> registers;
    std::istream& in = std::cin;
    std::ostream& out = std::cout;

    Program* curProgram = nullptr;
};

}
