#include "processor.hpp"

namespace vm {
    
void Processor::executeProgram(Program& program) {
    program.compile();
    curProgram = &program;
    Command* cur = program.getCurCommand();
    while (cur != nullptr) {
        cur->execute(*this);
        cur = program.getCurCommand();
    }
    curProgram = nullptr;
}

}