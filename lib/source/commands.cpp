#include "commands.hpp"
#include "processor.hpp"

namespace vm {

// Соответствие имени команды с самой командой
Command* createCommandByName(const std::string& name) {
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
    } else if (name == "sub") {
        return new Sub();
    } else if (name == "mul") {
        return new Mul();
    } else if (name == "div") {
        return new Div();
    } else if (name == "pop") {
        return new Pop();
    } else if (name == "push") {
        return new Push();
    } else if (name == "pushr") {
        return new Pushr();
    } else if (name == "popr") {
        return new Popr();
    } else if (name == "jmp") {
        return new Jump();
    } else if (name == "jeq") {
        return new JumpEQ();
    } else if (name == "jne") {
        return new JumpNEQ();
    } else if (name == "ja") {
        return new JumpG();
    } else if (name == "jae") {
        return new JumpGE();
    } else if (name == "jb") {
        return new JumpL();
    } else if (name == "jbe") {
        return new JumpLE();
    } else if (name == "call") {
        return new Call();
    } else if (name == "ret") {
        return new Ret();
    }

    return nullptr;
}


void In::execute(Processor& proc) {
    int value;
    proc.getInput() >> value;
    proc.getStack().push(value);
}

void Out::execute(Processor& proc) {
    proc.getOutput() << proc.getStack().pop() << std::endl;
}


void Add::execute(Processor& proc) {
    int a = proc.getStack().pop();
    int b = proc.getStack().pop();
    proc.getStack().push(a + b);
}

void Sub::execute(Processor& proc) {
    int a = proc.getStack().pop();
    int b = proc.getStack().pop();
    proc.getStack().push(b - a);
}

void Mul::execute(Processor& proc) {
    int a = proc.getStack().pop();
    int b = proc.getStack().pop();
    proc.getStack().push(a * b);
}

void Div::execute(Processor& proc) {
    int a = proc.getStack().pop();
    int b = proc.getStack().pop();
    proc.getStack().push(b / a);
}


void Pop::execute(Processor& proc) {
    proc.getStack().pop();
}

void Push::setArgs(const std::vector<std::string>& args) {
    value = std::stoi(args[0]);
}

void Push::execute(Processor& proc) {
    proc.getStack().push(value);
}


void Pushr::setArgs(const std::vector<std::string>& args) {
    reg = args[0];
}

void Pushr::execute(Processor& proc) {
    try {
        int value = proc.getRegister(reg);
        proc.getStack().push(value);
    } catch (const std::out_of_range& e) {
        throw CommandRuntimeError("Обращение к несуществующему регистру");
    }
}

void Popr::execute(Processor& proc) {
    proc.setRegister(reg, proc.getStack().pop());
}


void Jump::setArgs(const std::vector<std::string>& args) {
    label = args[0];
}

void Jump::execute(Processor& proc) {
    proc.getCurProgram().jumpToLabel(label);
}

void JumpEQ::execute(Processor& proc) {
    if (proc.getStack().pop() == proc.getStack().pop()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void JumpNEQ::execute(Processor& proc) {
    if (proc.getStack().pop() != proc.getStack().pop()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}
void JumpG::execute(Processor& proc) {
    if (proc.getStack().pop() > proc.getStack().pop()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void JumpGE::execute(Processor& proc) {
    if (proc.getStack().pop() >= proc.getStack().pop()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void JumpL::execute(Processor& proc) {
    if (proc.getStack().pop() < proc.getStack().pop()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void JumpLE::execute(Processor& proc) {
    if (proc.getStack().pop() <= proc.getStack().pop()) {
        proc.getCurProgram().jumpToLabel(label);
    }
}

void Call::execute(Processor& proc) {

}

void Ret::execute(Processor& proc) {

}

}