#include "processor.hpp"

namespace vm {
    
void Processor::executeProgram(Program& program) {
    curProgram = &program;
    Command* cur = program.getCurCommand();
    while (cur != nullptr) {
        cur->execute(*this);
        cur = program.getCurCommand();
    }
}

}