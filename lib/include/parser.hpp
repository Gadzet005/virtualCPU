#pragma once
#include <string>
#include <fstream>
#include <regex>
#include "program.hpp"
#include "commands.hpp"
#include "exceptions.hpp"

namespace vm {

namespace Parser {
    Program parseProgram(const std::string& path);
    bool validateCommandArg(const std::string& arg, Command::ArgType type);

    const std::map<std::string, std::regex> TOKENS = {
        {"Command", std::regex(R"([a-z]\w*)", std::regex::icase)},
        {"Label", std::regex(R"(([a-z]\w*):)", std::regex::icase)},
        {"LabelName", std::regex(R"([a-z]\w*)", std::regex::icase)},
        {"Reg", std::regex(R"([a-z]+)", std::regex::icase)},
        {"Number", std::regex(R"(-?\d+)")},
    };
};

}