#pragma once
#include <string>

namespace vm {

// Forward declarations
class Processor;

class Command {
public:
    virtual ~Command() {}

    virtual void execute(Processor& proc) = 0;
};

Command* createCommandByName(const std::string name);

class Begin : public Command {
public:
    void execute(Processor& proc) override {};
};

class End : public Command {
    void execute(Processor& proc) override {};
};

class In : public Command {
    void execute(Processor& proc) override;
};

class Out : public Command {
    void execute(Processor& proc) override;
};

class Add : public Command {
    void execute(Processor& proc) override;
};

class Sub : public Command {
    void execute(Processor& proc) override;
};

class Mul : public Command {
    void execute(Processor& proc) override;
};

class Div : public Command {
    void execute(Processor& proc) override;
};

}