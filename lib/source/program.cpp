#include "program.hpp"

namespace vm {

void Program::compile() {
    bool startFound = false;
    bool endFound = false;

    for (int i = 0; i < commands.size(); i++) {
        Command& cmd = *commands[i];

        if (typeid(cmd) == typeid(Begin)) {
            if (startFound) {
                throw ProgramError("Допускается только одна команда begin");
            }
            startFound = true;
        }

        if (typeid(cmd) == typeid(End)) {
            if (!startFound) {
                throw ProgramError("Команда end до команды begin");
            }
            if (endFound) {
                throw ProgramError("Допускается только одна команда end");
            }
            endFound = true;
        }

        if (startFound && endFound) {
            break;
        }
    }

    if (!startFound || !endFound) {
        throw ProgramError("Команда begin или end не найдены");
    }
}

size_t Program::findStart() const {
    for (size_t i = 0; i < commands.size(); i++) {
        if (typeid(*commands[i]) == typeid(Begin)) {
            return i;
        }
    }
    return commands.size();
}

void Program::addCommand(Command* cmd) {
    commands.push_back(std::unique_ptr<Command>(cmd));
}

void Program::addLabel(const std::string& label) {
    if (labels.find(label) != labels.end()) {
        throw ProgramError("Повторное использование метки " + label);
    }
    labels[label] = commands.size();
}

void Program::save(const std::string& path) const {
    std::ofstream file(path, std::ios::binary);
    std::string line = "hello world";
    file.write(line.data(), line.size());
}

Program Program::load(const std::string& path) {
    Program program;
    return program;
}


bool ProgramExecutor::finished() const {
    return currentIdx >= prog.commands.size();
}

Command& ProgramExecutor::getCurComand() const {
    return *prog.commands.at(currentIdx);
}

void ProgramExecutor::toNextCommand() {
    if (typeid(getCurComand()) == typeid(End)) {
        currentIdx = prog.commands.size();
    } else {
        currentIdx++;
    }
}

void ProgramExecutor::jumpToLabel(const std::string& label) {
    try {
        jumpToIdx(prog.labels.at(label));
    } catch (const std::out_of_range&) {
        throw ProgramError("Метка " + label + " не найдена");
    }
}

size_t ProgramExecutor::getCurrentIdx() const {
    return std::min(currentIdx, prog.commands.size());
}

}