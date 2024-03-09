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
    static Program parseProgram(const char* path);
    static bool validateCommandArg(const std::string& arg, ArgType type);
private:
    // Команды. Обязательно начинается с буквы, затем могут идти буквы или цифры
    inline static const std::regex COMMAND = std::regex(R"([a-zA-z]\w*)", std::regex::icase);
    // Метки. По аналогии с командами
    inline static const std::regex LABEL = std::regex(R"(([a-zA-z]\w*):)", std::regex::icase);
    inline static const std::regex LABEL_NAME = std::regex(R"([a-zA-z]\w*)", std::regex::icase);
    // Числа
    inline static const std::regex NUMBER = std::regex(R"(-?\d+)");
    // Регистры
    inline static const std::regex REG = std::regex(R"([a-zA-z]+)");
};

}