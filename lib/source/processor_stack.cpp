#include "processor_stack.hpp"

namespace vm {

void ProcessorStack::pushValue(int value) {
    auto toPush = std::shared_ptr<StackEntity>(new StackNumber(value));
    push(toPush);
}

void ProcessorStack::pushFunction(size_t calledFrom) {
    auto toPush = std::shared_ptr<StackEntity>(new StackFunction(calledFrom));
    push(toPush);
}

int ProcessorStack::popValue() {
    StackEntity* toPop = pop().get();
    if (toPop->getType() == StackEntity::Type::Number) {
        return static_cast<StackNumber*>(toPop)->getValue();
    } else {
        throw EmptyStackError("Вызов метода popValue на пустом стэке");
    }
}

size_t ProcessorStack::popFunction() {
    StackEntity* toPop;
    while (!empty()) {
        toPop = pop().get();
        if (toPop->getType() == StackEntity::Type::Function) {
            return static_cast<StackFunction*>(toPop)->getCalledFrom();
        }
    }
    throw EmptyStackError("Вызов метода popFunction на пустом стэке");
}

}