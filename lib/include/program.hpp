#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <fstream>
#include "commands.hpp"

namespace vm {

class Program {
public:
    void addCommand(std::shared_ptr<Command>&& cmd);
    void addCommand(Command* cmd);
    void addLabel(const std::string& label);
    
    void compile() const;
    size_t findStart() const;

    void save(const std::string& path) const;
    static Program load(const std::string& path);

    friend class ProgramExecutor;

private:
    std::vector<std::shared_ptr<Command>> commands;
    std::map<std::string, size_t> labels;
};

class ProgramExecutor {
public:
    ProgramExecutor(Program& program) : 
        prog(program), currentIdx(prog.findStart()) {};

    bool finished() const;
    Command& getCurComand() const;
    void toNextCommand();

    void jumpToLabel(const std::string& label);
    void jumpToIdx(size_t idx) { currentIdx = idx; };

    size_t getCurrentIdx() const;

private:
    Program& prog;
    size_t currentIdx;
};

}