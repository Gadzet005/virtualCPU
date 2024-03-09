#include "commands.hpp"
#include "processor.hpp"

namespace vm {

Command* createCommandByName(const std::string name) {
    if (name == "begin") {
        return new Begin();
    } else if (name == "end") {
        return new End();
    } else if (name == "in") {
        return new In();
    } else if (name == "out") {
        return new Out();
    } else if (name == "add") {
        return new Add();
    } else if (name == "sub") {
        return new Sub();
    } else if (name == "mul") {
        return new Mul();
    } else if (name == "div") {
        return new Div();
    } else {
        return nullptr;
    }
}

void In::execute(Processor& proc) {
    int value;
    proc.in >> value;
    proc.stack.push(value);
}

void Out::execute(Processor& proc) {
    int value = proc.stack.pop();
    proc.out << value << std::endl;
}

void Add::execute(Processor& proc) {
    int a = proc.stack.pop();
    int b = proc.stack.pop();
    proc.stack.push(a + b);
}

void Sub::execute(Processor& proc) {
    int a = proc.stack.pop();
    int b = proc.stack.pop();
    proc.stack.push(a - b);
}

void Mul::execute(Processor& proc) {
    int a = proc.stack.pop();
    int b = proc.stack.pop();
    proc.stack.push(a * b);
}

void Div::execute(Processor& proc) {
    int a = proc.stack.pop();
    int b = proc.stack.pop();
    proc.stack.push(a / b);
}

}