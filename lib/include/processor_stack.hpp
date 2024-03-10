#pragma once
#include <memory>
#include "stack.hpp"

namespace vm {

class StackEntity {
public:
    enum class Type {
        Number, Function
    };

    virtual StackEntity::Type getType() const = 0;
    virtual ~StackEntity() = default;
};

class StackNumber : public StackEntity {
public:
    StackNumber(int val) : value(val) {}
    StackEntity::Type getType() const override { return StackEntity::Type::Number; }
    int getValue() const { return value; }
private:
    int value;
};

class StackFunction : public StackEntity {
public:
    StackFunction(int idx) : calledFrom(idx) {}
    StackEntity::Type getType() const override { return StackEntity::Type::Function; }
    int getCalledFrom() const { return calledFrom; }
private:
    int calledFrom = 0;
};

class ProcessorStack : private Stack<std::shared_ptr<StackEntity>> {
public:
    ProcessorStack() = default;

    void pushValue(int value);
    void pushFunction(int calledFrom);
    int popValue();
    size_t popFunction();

    void clear() { clear(); }

private:
    ProcessorStack(const ProcessorStack& other) = delete;
    ProcessorStack& operator = (const ProcessorStack& other) = delete;
};

}
