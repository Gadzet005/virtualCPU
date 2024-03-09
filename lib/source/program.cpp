#include "program.hpp"

namespace vm {

void Program::addCommand(Command* cmd) {
    if (typeid(*cmd) == typeid(Begin)) {
        if (startFound) {
            throw MultipleUseError("Допускается только одна команда begin");
        }
        startIdx = commands.size();
        startFound = true;
    }
    if (typeid(*cmd) == typeid(End)) {
        if (!startFound) {
            throw ProgramError("Команда end до команды begin");
        }
        if (endFound) {
            throw MultipleUseError("Допускается только одна команда end");
        }
        endIdx = commands.size();
        endFound = true;
    }
    if (!endFound) {
        endIdx++;
    }
    if (!startFound) {
        currentIdx++;
    }

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

}