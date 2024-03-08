#include "parser.hpp"

namespace vm {

Program Parser::parseProgram(const char* path) {
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
        } else if (std::regex_match(token, result, LABEL)) {
            program.addLabel(result[1]);
        } else if (std::regex_match(token, result, COMMAND)) {
            Command* command = createCommandByName(result[0]);
            if (command == nullptr) {
                throw ParseError(std::string("Неизвестная команда: ") + token, lineIdx);
            }
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