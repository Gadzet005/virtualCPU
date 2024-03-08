#include "program.hpp"

namespace vm {

void Program::addCommand(Command* cmd) {
    commands.push_back(std::unique_ptr<Command>(cmd));
}

void Program::addLabel(const std::string& label) {
    labels.insert({label, commands.size()});
}

}