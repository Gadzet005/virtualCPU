#include "commands.hpp"
#include "processor.hpp"

namespace vm {

// Соответствие имени команды с самой командой
std::shared_ptr<Command> createCommandByName(std::string name) {
    // lowercase
    std::transform(name.begin(), name.end(), name.begin(), [](char c){ return std::tolower(c); });

    #define ADD_COMMAND(cmd) if (cmd::name == name) return std::make_shared<cmd>();

    ADD_COMMAND(Begin);
    ADD_COMMAND(End);
    ADD_COMMAND(In);
    ADD_COMMAND(Out);
    ADD_COMMAND(Add);
    ADD_COMMAND(Sub);
    ADD_COMMAND(Mul);
    ADD_COMMAND(Div);
    ADD_COMMAND(Pop);
    ADD_COMMAND(Push);
    ADD_COMMAND(Pushr);
    ADD_COMMAND(Popr);
    ADD_COMMAND(Jump);
    ADD_COMMAND(JumpEQ);
    ADD_COMMAND(JumpNEQ);
    ADD_COMMAND(JumpG);
    ADD_COMMAND(JumpGE);
    ADD_COMMAND(JumpL);
    ADD_COMMAND(JumpLE);
    ADD_COMMAND(Call);
    ADD_COMMAND(Ret);
    return nullptr;

    #undef ADD_COMMAND
}

void In::execute(Processor& proc, ProgramExecutor& executor) {
    long long value;
    proc.getInput() >> value;
    proc.getStack().pushValue(value);
}

void Out::execute(Processor& proc, ProgramExecutor& executor) {
    proc.getOutput() << proc.getStack().popValue() << std::endl;
}


void Add::execute(Processor& proc, ProgramExecutor& executor) {
    long long a = proc.getStack().popValue();
    long long b = proc.getStack().popValue();
    proc.getStack().pushValue(a + b);
}

void Sub::execute(Processor& proc, ProgramExecutor& executor) {
    long long a = proc.getStack().popValue();
    long long b = proc.getStack().popValue();
    proc.getStack().pushValue(b - a);
}

void Mul::execute(Processor& proc, ProgramExecutor& executor) {
    long long a = proc.getStack().popValue();
    long long b = proc.getStack().popValue();
    proc.getStack().pushValue(a * b);
}

void Div::execute(Processor& proc, ProgramExecutor& executor) {
    long long a = proc.getStack().popValue();
    long long b = proc.getStack().popValue();
    proc.getStack().pushValue(b / a);
}


void Pop::execute(Processor& proc, ProgramExecutor& executor) {
    proc.getStack().popValue();
}

void Push::setArgs(const std::vector<std::string>& args) {
    value = std::stoll(args[0]);
}

void Push::execute(Processor& proc, ProgramExecutor& executor) {
    proc.getStack().pushValue(value);
}


void Pushr::setArgs(const std::vector<std::string>& args) {
    reg = args[0];
}

void Pushr::execute(Processor& proc, ProgramExecutor& executor) {
    try {
        long long value = proc.getRegister(reg);
        proc.getStack().pushValue(value);
    } catch (const std::out_of_range& e) {
        throw CommandRuntimeError("Обращение к несуществующему регистру");
    }
}

void Popr::execute(Processor& proc, ProgramExecutor& executor) {
    proc.setRegister(reg, proc.getStack().popValue());
}


void Jump::setArgs(const std::vector<std::string>& args) {
    label = args[0];
}

void Jump::execute(Processor& proc, ProgramExecutor& executor) {
    executor.jumpToLabel(label);
}

void JumpEQ::execute(Processor& proc, ProgramExecutor& executor) {
    if (proc.getStack().popValue() == proc.getStack().popValue()) {
        executor.jumpToLabel(label);
    }
}

void JumpNEQ::execute(Processor& proc, ProgramExecutor& executor) {
    if (proc.getStack().popValue() != proc.getStack().popValue()) {
        executor.jumpToLabel(label);
    }
}
void JumpG::execute(Processor& proc, ProgramExecutor& executor) {
    if (proc.getStack().popValue() > proc.getStack().popValue()) {
        executor.jumpToLabel(label);
    }
}

void JumpGE::execute(Processor& proc, ProgramExecutor& executor) {
    if (proc.getStack().popValue() >= proc.getStack().popValue()) {
        executor.jumpToLabel(label);
    }
}

void JumpL::execute(Processor& proc, ProgramExecutor& executor) {
    if (proc.getStack().popValue() < proc.getStack().popValue()) {
        executor.jumpToLabel(label);
    }
}

void JumpLE::execute(Processor& proc, ProgramExecutor& executor) {
    if (proc.getStack().popValue() <= proc.getStack().popValue()) {
        executor.jumpToLabel(label);
    }
}

void Call::execute(Processor& proc, ProgramExecutor& executor) {
    size_t calledFrom = executor.getCurrentIdx();
    proc.getStack().pushFunction(calledFrom);
    executor.jumpToLabel(label);
}

void Ret::execute(Processor& proc, ProgramExecutor& executor) {
    try {
        size_t calledFrom = proc.getStack().popFunction();
        executor.jumpToIdx(calledFrom);
    } catch (const EmptyStackError& e) {
        throw CommandRuntimeError("Вызов команды ret без вызова команды call");
    }
}

}