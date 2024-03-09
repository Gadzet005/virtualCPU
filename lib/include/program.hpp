#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "commands.hpp"

namespace vm {

class ProgramError : public std::exception {
public:
    ProgramError(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    const std::string msg;
};

class MultipleUseError : public ProgramError {
public:
    MultipleUseError(const std::string& message) : ProgramError(message) {}
};

class Program {
public:
    void addCommand(Command* cmd);
    void addLabel(const std::string& label);
    Command* getCurCommand();
    void jumpToLabel(const std::string& label);

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