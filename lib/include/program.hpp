#pragma once
#include <vector>
#include <map>
#include <memory>
#include "commands.hpp"

namespace vm {

class Program {
public:
    void addCommand(Command* cmd);
    void addLabel(const std::string& label);

private:
    std::vector<std::unique_ptr<Command>> commands;
    std::map<std::string, int> labels;
    int startIdx = 0;
    int endIdx = 0;
};

}