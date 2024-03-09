#pragma once
#include <string>
#include <vector>

namespace vm {

// Forward declarations
class Processor;

class ArgError : public std::exception {
public:
    ArgError(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    const std::string msg;
};

enum class ArgType {
    Int, 
    Reg,
    Label
};

class Command {
public:
    virtual ~Command() {}

    // Выполнение команды
    virtual void execute(Processor& proc) = 0;
    // Передача аргументов в команду
    virtual void setArgs(const std::vector<std::string>& args) {};
    // Получить типы аргументов команды
    virtual std::vector<ArgType> getArgTypes() const { return {}; }
};

Command* createCommandByName(const std::string name);

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
    std::vector<ArgType> getArgTypes() const { return {ArgType::Int}; }

private:
    int value;
};

class Pushr : public Command {
public:
    void execute(Processor& proc) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Reg}; }

private:
    std::string reg;
};

class Popr : public Command {
public:
    void execute(Processor& proc) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Reg}; }

private:
    std::string reg;
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

}