#pragma once
#include <string>
#include <vector>
#include "exceptions.hpp"

namespace vm {

// Forward declarations
class Processor;

class Command {
public:
    enum class ArgType {
        Number, Reg, Label
    };

    // Выполнение команды
    virtual void execute(Processor& proc) = 0;
    // Передача аргументов в команду
    virtual void setArgs(const std::vector<std::string>& args) {};
    // Получить типы аргументов команды
    virtual std::vector<ArgType> getArgTypes() const { return {}; }

    virtual ~Command() = default;
};

Command* createCommandByName(const std::string& name);

class Begin : public Command {
public:
    void execute(Processor& proc) override {};
};

class End : public Command {
public:
    void execute(Processor& proc) override {};
};

class In : public Command {
public:
    void execute(Processor& proc) override;
};

class Out : public Command {
public:
    void execute(Processor& proc) override;
};

class Add : public Command {
public:
    void execute(Processor& proc) override;
};

class Sub : public Command {
public:
    void execute(Processor& proc) override;
};

class Mul : public Command {
public:
    void execute(Processor& proc) override;
};

class Div : public Command {
public:
    void execute(Processor& proc) override;
};

class Pop : public Command {
public:
    void execute(Processor& proc) override;
};

class Push : public Command {
public:
    void execute(Processor& proc) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Number}; }

private:
    int value;
};

class Pushr : public Command {
public:
    void execute(Processor& proc) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Reg}; }

protected:
    std::string reg;
};

class Popr : public Pushr {
    void execute(Processor& proc) override;
};

class Jump : public Command {
public:
    void execute(Processor& proc) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Label}; }

protected:
    std::string label;
};

class JumpEQ : public Jump {
    void execute(Processor& proc) override;
};

class JumpNEQ : public Jump {
    void execute(Processor& proc) override;
};

class JumpG : public Jump {
    void execute(Processor& proc) override;
};

class JumpGE : public Jump {
    void execute(Processor& proc) override;
};

class JumpL : public Jump {
    void execute(Processor& proc) override;
};

class JumpLE : public Jump {
    void execute(Processor& proc) override;
};

class Call : public Jump {
    void execute(Processor& proc) override;
};

class Ret : public Command {
    void execute(Processor& proc) override;
};

}