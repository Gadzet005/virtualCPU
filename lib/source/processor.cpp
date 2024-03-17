#include "processor.hpp"

namespace vm {
    
void Processor::executeProgram(Program& program) {
    ProgramExecutor executor(program);
    while (!executor.finished()) {
        Command& cur = executor.getCurComand();
        executor.toNextCommand();
        cur.execute(*this, executor);
    }
}

void Processor::clear() {
    stack.clear();
    registers.clear();
}

}