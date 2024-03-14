#include "parser.hpp"

namespace vm {

void toLower(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](char c){ return std::tolower(c); });
}

bool Parser::validateCommandArg(const std::string& arg, Command::ArgType type) {
    switch (type) {
        case Command::ArgType::Number:
            return std::regex_match(arg, TOKENS.at("Number"));
        case Command::ArgType::Reg:
            return std::regex_match(arg, TOKENS.at("Reg"));
        case Command::ArgType::Label:
            return std::regex_match(arg, TOKENS.at("LabelName"));
    }
    return false;
}

Program Parser::parseProgram(const std::string& path) {
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Не удалось открыть файл: ") + path);
    }

    Program program;
    std::string line;
    for (int lineIdx = 1; std::getline(file, line); lineIdx++) {
        if (!line.empty() && line.back() == '\n') { 
            line.pop_back();
        }
        std::stringstream lineStream(line);
        std::string token;
        lineStream >> token;

        std::smatch result;
        if (token.empty() || token.starts_with("//")) {
            continue;
        } else if (std::regex_match(token, result, TOKENS.at("Label"))) {
            program.addLabel(result[1]);
        } else if (std::regex_match(token, result, TOKENS.at("Command"))) {
            toLower(token);
            Command* command = createCommandByName(token);
            if (command == nullptr) {
                throw ParseError(std::string("Неизвестная команда: ") + token, lineIdx);
            }
            
            // Аргументы команды
            std::string arg;
            std::vector<std::string> args;
            std::vector<Command::ArgType> types = command->getArgTypes();
            for (int i = 0; i < types.size() && lineStream >> arg; i++) {
                if (!validateCommandArg(arg, types[i])) {
                    throw ParseError(std::string("Неверный тип аргумента: ") + arg, lineIdx);
                }
                args.push_back(arg);
            }

            if (args.size() != types.size()) {
                throw ParseError(std::string("Слишком мало аргументов для команды: ") + token, lineIdx);
            }

            command->setArgs(args);
            program.addCommand(command);
        } else {
            throw ParseError("Ошибка синтаксиса", lineIdx);
        }

        // Остаток строки
        std::string residual;
        lineStream >> residual;
        if (!residual.empty() && !residual.starts_with("//")) {
            throw ParseError("Ошибка синтаксиса", lineIdx);
        }
    }
    
    return program;
}

}