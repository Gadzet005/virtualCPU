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
    StackFunction(size_t idx) : calledFrom(idx) {}
    StackEntity::Type getType() const override { return StackEntity::Type::Function; }
    size_t getCalledFrom() const { return calledFrom; }
private:
    size_t calledFrom;
};

class ProcessorStack : private Stack<std::shared_ptr<StackEntity>> {
public:
    ProcessorStack() = default;

    void pushValue(int value);
    void pushFunction(size_t calledFrom);
    int popValue();
    size_t popFunction();

    void clear() { Stack<std::shared_ptr<StackEntity>>::clear(); }
};

}
