#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "commands.hpp"
#include "exceptions.hpp"

namespace vm {

class Program {
public:
    void addCommand(Command* cmd);
    void addLabel(const std::string& label);
    Command* getCurCommand();
    void jumpToLabel(const std::string& label);

    void compile();
    bool isCompiled() const { return compiled; };

private:
    std::vector<std::unique_ptr<Command>> commands;
    std::map<std::string, int> labels;

    size_t currentIdx = 0;

    bool compiled = false;
};

}