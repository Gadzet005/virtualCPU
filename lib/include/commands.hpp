#pragma once
#include <string>
#include <vector>
#include <memory>
#include <string_view>
#include <fstream>
#include <map>
#include "exceptions.hpp"

namespace vm {

// Forward declarations
class Processor;
class ProgramExecutor;


enum class CommandType {
    Begin, End, In, Out, Add, Sub, Mul, Div, Push, Pop, Pushr, Popr,
    Jump, JumpEQ, JumpNEQ, JumpG, JumpGE, JumpL, JumpLE, Call, Ret
};

class Command {
public:
    enum class ArgType {
        Number, Reg, Label
    };

    // Тип команды
    virtual CommandType getType() const = 0;

    // Выполнение команды
    virtual void execute(Processor& proc, ProgramExecutor& executor) = 0;

    // Передача аргументов в команду
    virtual void setArgs(const std::vector<std::string>& args) {}
    // Получить типы аргументов команды
    virtual std::vector<ArgType> getArgTypes() const { return {}; }

    // Сохранить команду
    virtual void save(std::ofstream& file) const { file << static_cast<int>(getType()); }
    // Загрузить команду
    virtual void load(std::ifstream& file) {}

    virtual ~Command() = default;
};

std::shared_ptr<Command> createCommandByType(CommandType name);
std::shared_ptr<Command> createCommandByName(std::string name);


class Begin : public Command {
public:
    static constexpr CommandType type = CommandType::Begin;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override {}
};

class End : public Command {
public:
    static constexpr CommandType type = CommandType::End;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override {}
};

class In : public Command {
public:
    static constexpr CommandType type = CommandType::In;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Out : public Command {
public:
    static constexpr CommandType type = CommandType::Out;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Add : public Command {
public:
    static constexpr CommandType type = CommandType::Add;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Sub : public Command {
public:
    static constexpr CommandType type = CommandType::Sub;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Mul : public Command {
public:
        static constexpr CommandType type = CommandType::Mul;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Div : public Command {
public:
    static constexpr CommandType type = CommandType::Div;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Pop : public Command {
public:
    static constexpr CommandType type = CommandType::Pop;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Push : public Command {
public:
    static constexpr CommandType type = CommandType::Push;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;

    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Number}; }

    void save(std::ofstream& file) const override { Command::save(file); file << " " << value; }
    void load(std::ifstream& file) override { file >> value; }

private:
    long long value;
};

class Pushr : public Command {
public:
    static constexpr CommandType type = CommandType::Pushr;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Reg}; }

    void save(std::ofstream& file) const override { Command::save(file); file << " " << reg; }
    void load(std::ifstream& file) override { file >> reg; }

protected:
    std::string reg;
};

class Popr : public Pushr {
public:
    static constexpr CommandType type = CommandType::Popr;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Jump : public Command {
public:
    static constexpr CommandType type = CommandType::Jump;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Label}; }

    void save(std::ofstream& file) const override { Command::save(file); file << " " << label; }
    void load(std::ifstream& file) override { file >> label; }

protected:
    std::string label;
};

class JumpEQ : public Jump {
public:
    static constexpr CommandType type = CommandType::JumpEQ;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpNEQ : public Jump {
public:
    static constexpr CommandType type = CommandType::JumpNEQ;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpG : public Jump {
public:
    static constexpr CommandType type = CommandType::JumpG;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpGE : public Jump {
public:
    static constexpr CommandType type = CommandType::JumpGE;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpL : public Jump {
public:
    static constexpr CommandType type = CommandType::JumpL;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class JumpLE : public Jump {
public:
    static constexpr CommandType type = CommandType::JumpLE;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Call : public Jump {
public:
    static constexpr CommandType type = CommandType::Call;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

class Ret : public Command {
public:
    static constexpr CommandType type = CommandType::Ret;
    CommandType getType() const override { return type; }

    void execute(Processor& proc, ProgramExecutor& executor) override;
};

}