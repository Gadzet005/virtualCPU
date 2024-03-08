#include "commands.hpp"

namespace vm {

Command* createCommandByName(const std::string name) {
    if (name == "begin") {
        return new Begin();
    } else if (name == "end") {
        return new End();
    } else if (name == "in") {
        return new In();
    } else if (name == "out") {
        return new Out();
    } else if (name == "add") {
        return new Add();
    } else {
        return nullptr;
    }
}

}