#pragma once
#include <string>
#include <fstream>
#include <stdexcept>
#include <regex>
#include "program.hpp"
#include "commands.hpp"

namespace vm {

class ParseError : public std::exception {
public:
    ParseError(const std::string& message, int lineIdx) : msg(
        "[Строка " + std::to_string(lineIdx) + "] " + std::string(message)
    ) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

class Parser {
public:
    Program parseProgram(const char* path);
private:
    // Команды. Обязательно начинается с буквы, затем могут идти буквы или цифры
    const std::regex COMMAND = std::regex(R"([a-zA-z]\w*)", std::regex::icase);
    // Метки, по аналогии с командами
    const std::regex LABEL = std::regex(R"(([a-zA-z]\w*):)", std::regex::icase);
};

}