#include "program.hpp"

namespace vm {

void Program::addCommand(Command* cmd) {
    if (typeid(*cmd) == typeid(Begin)) {
        if (startFound) {
            throw MultipleUseError("Допускается только одна команда begin");
        }
        startIdx = commands.size();
    }
    if (typeid(*cmd) == typeid(End)) {
        if (endFound) {
            throw MultipleUseError("Допускается только одна команда end");
        }
        endIdx = commands.size();
    }
    if (!endFound) {
        endIdx++;
    }

    commands.push_back(std::unique_ptr<Command>(cmd));
}

void Program::addLabel(const std::string& label) {
    if (labels.find(label) != labels.end()) {
        throw MultipleUseError("Повторное использование метки " + label);
    }
    labels.insert({label, commands.size()});
}

Command* Program::getCurCommand() {
    if (currentIdx >= endIdx) {
        return nullptr;
    }
    return commands.at(currentIdx++).get();
}

}