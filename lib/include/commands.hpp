#pragma once
#include <string>
#include <vector>
#include <memory>
#include <string_view>
#include <fstream>
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
    virtual void setArgs(const std::vector<std::string>& args) {}
    // Получить типы аргументов команды
    virtual std::vector<ArgType> getArgTypes() const { return {}; }
    // Сохранить команду
    virtual void save(std::ofstream& file) const = 0;

    virtual ~Command() = default;
};

std::shared_ptr<Command> createCommandByName(std::string name);

class Begin : public Command {
public:
    static constexpr std::string_view name = "begin";
    void execute(Processor& proc, ProgramExecutor& executor) override {}
    void save(std::ofstream& file) const override { file << name; }
};

class End : public Command {
public:
    static constexpr std::string_view name = "end";
    void execute(Processor& proc, ProgramExecutor& executor) override {}
    void save(std::ofstream& file) const override { file << name; }
};

class In : public Command {
public:
    static constexpr std::string_view name = "in";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name; }
};

class Out : public Command {
public:
    static constexpr std::string_view name = "out";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name; }
};

class Add : public Command {
public:
    static constexpr std::string_view name = "add";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name; }
};

class Sub : public Command {
public:
    static constexpr std::string_view name = "sub";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name; }
};

class Mul : public Command {
public:
    static constexpr std::string_view name = "mul";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name; }
};

class Div : public Command {
public:
    static constexpr std::string_view name = "div";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name; }
};

class Pop : public Command {
public:
    static constexpr std::string_view name = "pop";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name; }
};

class Push : public Command {
public:
    static constexpr std::string_view name = "push";

    void execute(Processor& proc, ProgramExecutor& executor) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Number}; }

    void save(std::ofstream& file) const override { file << name << " " << value; }

private:
    long long value;
};

class Pushr : public Command {
public:
    static constexpr std::string_view name = "pushr";

    void execute(Processor& proc, ProgramExecutor& executor) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Reg}; }

    void save(std::ofstream& file) const override { file << name << " " << reg; }

protected:
    std::string reg;
};

class Popr : public Pushr {
public:
    static constexpr std::string_view name = "popr";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name << " " << reg; }
};

class Jump : public Command {
public:
    static constexpr std::string_view name = "jmp";

    void execute(Processor& proc, ProgramExecutor& executor) override;
    void setArgs(const std::vector<std::string>& args) override;
    std::vector<ArgType> getArgTypes() const { return {ArgType::Label}; }

    void save(std::ofstream& file) const override { file << name << " " << label; }

protected:
    std::string label;
};

class JumpEQ : public Jump {
public:
    static constexpr std::string_view name = "jeq";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name << " " << label; }
};

class JumpNEQ : public Jump {
public:
    static constexpr std::string_view name = "jne";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name << " " << label; }
};

class JumpG : public Jump {
public:
    static constexpr std::string_view name = "ja";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name << " " << label; }
};

class JumpGE : public Jump {
public:
    static constexpr std::string_view name = "jae";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name << " " << label; }
};

class JumpL : public Jump {
public:
    static constexpr std::string_view name = "jb";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name << " " << label; }
};

class JumpLE : public Jump {
public:
    static constexpr std::string_view name = "jbe";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name << " " << label; }
};

class Call : public Jump {
public:
    static constexpr std::string_view name = "call";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name << " " << label; }
};

class Ret : public Command {
public:
    static constexpr std::string_view name = "ret";
    void execute(Processor& proc, ProgramExecutor& executor) override;
    void save(std::ofstream& file) const override { file << name; }
};

}