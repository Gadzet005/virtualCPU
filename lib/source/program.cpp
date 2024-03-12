#include "program.hpp"

namespace vm {

void Program::compile() {
    if (isCompiled()) {
        currentIdx = beginIdx;
        return;
    }

    size_t startIdx = 0;
    bool startFound = false;
    bool endFound = false;

    for (int i = 0; i < commands.size(); i++) {
        Command* cmd = commands[i].get();
        if (typeid(*cmd) == typeid(Begin)) {
            if (startFound) {
                throw MultipleUseError("Допускается только одна команда begin");
            }
            startIdx = i;
            startFound = true;
        }
        if (typeid(*cmd) == typeid(End)) {
            if (!startFound) {
                throw ProgramError("Команда end до команды begin");
            }
            if (endFound) {
                throw MultipleUseError("Допускается только одна команда end");
            }
            endFound = true;
        }
    }

    if (!startFound || !endFound) {
        throw ProgramError("Команда begin или end не найдены");
    }

    currentIdx = startIdx;
    beginIdx = startIdx;
    compiled = true;
}

void Program::addCommand(Command* cmd) {
    commands.push_back(std::unique_ptr<Command>(cmd));
}

void Program::addLabel(const std::string& label) {
    if (labels.find(label) != labels.end()) {
        throw MultipleUseError("Повторное использование метки " + label);
    }
    labels[label] = commands.size();
}

Command* Program::getCurCommand() {
    if (currentIdx >= commands.size()) {
        return nullptr;
    }
    Command* cur = commands.at(currentIdx++).get();
    if (typeid(*cur) == typeid(End)) {
        return nullptr;
    }
    return cur;
}

void Program::jumpToLabel(const std::string& label) {
    if (labels.find(label) == labels.end()) {
        throw ProgramError("Метка " + label + " не найдена");
    }
    currentIdx = labels[label];
}

void Program::jumpToIdx(size_t idx) {
    if (idx > commands.size()) {
        throw ProgramError("Невозможно прыгнуть по индексу: " + std::to_string(idx));
    }
    currentIdx = idx;
}

}