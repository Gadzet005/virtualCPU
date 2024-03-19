#include "commands.hpp"
#include "processor.hpp"

namespace vm {

const std::map<std::string, CommandType> nameToType {
    {"begin", CommandType::Begin},
    {"end", CommandType::End},
    {"in", CommandType::In},
    {"out", CommandType::Out},
    {"add", CommandType::Add},
    {"sub", CommandType::Sub},
    {"mul", CommandType::Mul},
    {"div", CommandType::Div},
    {"push", CommandType::Push},
    {"pop", CommandType::Pop},
    {"pushr", CommandType::Pushr},
    {"popr", CommandType::Popr},
    {"jmp", CommandType::Jump},
    {"jeq", CommandType::JumpEQ},
    {"jne", CommandType::JumpNEQ},
    {"ja", CommandType::JumpG},
    {"jae", CommandType::JumpGE},
    {"jb", CommandType::JumpL},
    {"jbe", CommandType::JumpLE},
    {"call", CommandType::Call},
    {"ret", CommandType::Ret},
};

std::shared_ptr<Command> createCommandByType(CommandType type) {
    switch (type) {
        case CommandType::Begin:    return std::make_shared<Begin>();
        case CommandType::End:      return std::make_shared<End>();
        case CommandType::In:       return std::make_shared<In>();
        case CommandType::Out:      return std::make_shared<Out>();
        case CommandType::Add:      return std::make_shared<Add>();
        case CommandType::Sub:      return std::make_shared<Sub>();
        case CommandType::Mul:      return std::make_shared<Mul>();
        case CommandType::Div:      return std::make_shared<Div>();
        case CommandType::Push:     return std::make_shared<Push>();
        case CommandType::Pop:      return std::make_shared<Pop>();
        case CommandType::Pushr:    return std::make_shared<Pushr>();
        case CommandType::Popr:     return std::make_shared<Popr>();
        case CommandType::Jump:     return std::make_shared<Jump>();
        case CommandType::JumpEQ:   return std::make_shared<JumpEQ>();
        case CommandType::JumpNEQ:  return std::make_shared<JumpNEQ>();
        case CommandType::JumpG:    return std::make_shared<JumpG>();
        case CommandType::JumpGE:   return std::make_shared<JumpGE>();
        case CommandType::JumpL:    return std::make_shared<JumpL>();
        case CommandType::JumpLE:   return std::make_shared<JumpLE>();
        case CommandType::Call:     return std::make_shared<Call>();
        case CommandType::Ret:      return std::make_shared<Ret>();
        default:                    return nullptr;
    }
}

std::shared_ptr<Command> createCommandByName(std::string name) {
    // lowercase
    std::transform(name.begin(), name.end(), name.begin(), [](char c){ return std::tolower(c); });
    CommandType type = nameToType.at(name);
    return createCommandByType(type);
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