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
    bool validateCommandArg(const std::string& arg, ArgType type);

    // Команды. Обязательно начинается с буквы, затем могут идти буквы или цифры
    const std::regex COMMAND = std::regex(R"([a-z]\w*)", std::regex::icase);
    // Метки. По аналогии с командами
    const std::regex LABEL = std::regex(R"(([a-z]\w*):)", std::regex::icase);
    const std::regex LABEL_NAME = std::regex(R"([a-z]\w*)", std::regex::icase);
    // Числа
    const std::regex NUMBER = std::regex(R"(-?\d+)");
    // Регистры
    const std::regex REG = std::regex(R"([a-z]+)", std::regex::icase);
};

}