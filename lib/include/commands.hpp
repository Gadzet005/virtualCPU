#pragma once
#include <string>

namespace vm {

class Command {
public:
    virtual ~Command() {}

    virtual void execute() = 0;
};

Command* createCommandByName(const std::string name);

class Begin : public Command {
public:
    void execute() override {};
};

class End : public Command {
    void execute() override {};
};

class In : public Command {
    void execute() override {};
};

class Out : public Command {
    void execute() override {};
};

class Add : public Command {
    void execute() override {};
};

}