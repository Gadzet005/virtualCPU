#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "commands.hpp"

namespace vm {

class MultipleUseError : public std::exception {
public:
    MultipleUseError(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    const std::string msg;
};

class Program {
public:
    void addCommand(Command* cmd);
    void addLabel(const std::string& label);
    Command* getCurCommand();

private:
    std::vector<std::unique_ptr<Command>> commands;
    std::map<std::string, int> labels;
    size_t startIdx = 0;
    bool startFound = false;
    size_t endIdx = 0;
    bool endFound = false;
    size_t currentIdx = 0;
};

}