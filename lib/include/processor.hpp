#pragma once
#include <iostream>
#include <map>
#include "stack.hpp"
#include "program.hpp"
#include "processor_stack.hpp"

namespace vm {

class Processor {
public:
    Processor() = default;
    Processor(std::istream& input, std::ostream& output) : in(input), out(output) {};

    std::istream& getInput() const { return in; }
    std::ostream& getOutput() const { return out; }
    ProcessorStack& getStack() { return stack; }

    void setRegister(const std::string& name, long long value) { registers[name] = value; }
    long long getRegister(const std::string& name) const { return registers.at(name); }

    void executeProgram(Program& program);

    void clear();

private:
    ProcessorStack stack;
    std::map<std::string, long long> registers;
    std::istream& in = std::cin;
    std::ostream& out = std::cout;
};

}
