#pragma once
#include <string>
#include <vector>
#include <memory>
#include "exceptions.hpp"

namespace vm {

// Forward declarations
class Processor;
class ProgramExecutor;

class Command {
public:
    enum class ArgType {
        Number, Reg, Label
    };

    // Выполнение команды
    virtual void execute(Processor& proc, ProgramExecutor& executor) = 0;
    // Передача аргументов в команду
    virtual void setArgs(const std::vector<std::string>& args) {};
    // Получить типы аргументов команды
    virtual std::vector<ArgType> getArgTypes() const { return {}; }

    virtual ~Command() = default;
};

std::shared_ptr<Command> createCommandByName(std::string name);

class Begin : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override {};
};

class End : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override {};
};

class In : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Out : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Add : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Sub : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Mul : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Div : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Pop : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Push : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Number}; }

private:
    long long value;
};

class Pushr : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Reg}; }

protected:
    std::string reg;
};

class Popr : public Pushr {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Jump : public Command {
public:
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Label}; }

protected:
    std::string label;
};

class JumpEQ : public Jump {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpNEQ : public Jump {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpG : public Jump {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpGE : public Jump {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpL : public Jump {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpLE : public Jump {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Call : public Jump {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Ret : public Command {
    void execute(Processor& proc, ProgramExecutor& executor) override;
};

}