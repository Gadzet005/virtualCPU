#include "commands.hpp"
#include "processor.hpp"

namespace vm {

// Соответствие имени команды с самой командой
Command* createCommandByName(std::string name) {
    // lowercase
    std::transform(name.begin(), name.end(), name.begin(), [](char c){ return std::tolower(c); });

    #define ADD_COMMAND(objName, obj) if (name == objName) return new obj();

    ADD_COMMAND("begin", Begin);
    ADD_COMMAND("end", End);
    ADD_COMMAND("in", In);
    ADD_COMMAND("out", Out);
    ADD_COMMAND("add", Add);
    ADD_COMMAND("sub", Sub);
    ADD_COMMAND("mul", Mul);
    ADD_COMMAND("div", Div);
    ADD_COMMAND("pop", Pop);
    ADD_COMMAND("push", Push);
    ADD_COMMAND("pushr", Pushr);
    ADD_COMMAND("popr", Popr);
    ADD_COMMAND("jmp", Jump);
    ADD_COMMAND("jeq", JumpEQ);
    ADD_COMMAND("jne", JumpNEQ);
    ADD_COMMAND("ja", JumpG);
    ADD_COMMAND("jae", JumpGE);
    ADD_COMMAND("jb", JumpL);
    ADD_COMMAND("jbe", JumpLE);
    ADD_COMMAND("call", Call);
    ADD_COMMAND("ret", Ret);
    return nullptr;

    #undef ADD_COMMAND
}

void In::execute(Processor& proc) {
    int value;
    proc.getInput() >> value;
    proc.getStack().pushValue(value);
}

void Out::execute(Processor& proc) {
    proc.getOutput() << proc.getStack().popValue() << std::endl;
}


void Add::execute(Processor& proc) {
    int a = proc.getStack().popValue();
    int b = proc.getStack().popValue();
    proc.getStack().pushValue(a + b);
}

void Sub::execute(Processor& proc) {
    int a = proc.getStack().popValue();
    int b = proc.getStack().popValue();
    proc.getStack().pushValue(b - a);
}

void Mul::execute(Processor& proc) {
    int a = proc.getStack().popValue();
    int b = proc.getStack().popValue();
    proc.getStack().pushValue(a * b);
}

void Div::execute(Processor& proc) {
    int a = proc.getStack().popValue();
    int b = proc.getStack().popValue();
    proc.getStack().pushValue(b / a);
}


void Pop::execute(Processor& proc) {
    proc.getStack().popValue();
}

void Push::setArgs(const std::vector<std::string>& args) {
    value = std::stoi(args[0]);
}

void Push::execute(Processor& proc) {
    proc.getStack().pushValue(value);
}


void Pushr::setArgs(const std::vector<std::string>& args) {
    reg = args[0];
}

void Pushr::execute(Processor& proc) {
    try {
        int value = proc.getRegister(reg);
        proc.getStack().pushValue(value);
    } catch (const std::out_of_range& e) {
        throw CommandRuntimeError("Обращение к несуществующему регистру");
    }
}

void Popr::execute(Processor& proc) {
    proc.setRegister(reg, proc.getStack().popValue());
}


void Jump::setArgs(const std::vector<std::string>& args) {
    label = args[0];
}

void Jump::execute(Processor& proc) {
    proc.getCurProgram().jumpToLabel(label);
}

void JumpEQ::execute(Processor& proc) {
    if (proc.getStack().popValue() == proc.getStack().popValue()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void JumpNEQ::execute(Processor& proc) {
    if (proc.getStack().popValue() != proc.getStack().popValue()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}
void JumpG::execute(Processor& proc) {
    if (proc.getStack().popValue() > proc.getStack().popValue()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void JumpGE::execute(Processor& proc) {
    if (proc.getStack().popValue() >= proc.getStack().popValue()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void JumpL::execute(Processor& proc) {
    if (proc.getStack().popValue() < proc.getStack().popValue()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void JumpLE::execute(Processor& proc) {
    if (proc.getStack().popValue() <= proc.getStack().popValue()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void Call::execute(Processor& proc) {
    size_t calledFrom = proc.getCurProgram().getCurIdx();
    proc.getStack().pushFunction(calledFrom);
    proc.getCurProgram().jumpToLabel(label);
}

void Ret::execute(Processor& proc) {
    try {
        size_t calledFrom = proc.getStack().popFunction();
        proc.getCurProgram().jumpToIdx(calledFrom);
    } catch (const EmptyStackError& e) {
        throw CommandRuntimeError("Вызов команды ret без вызова команды call");
    }
}

}