#pragma once
#include <stdexcept>

namespace vm {

class BaseError : public std::exception {
public:
    BaseError(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    const std::string msg;
};

class CommandRuntimeError : public BaseError {
public:
    CommandRuntimeError(const std::string& message) : BaseError(message) {}
};

class ParseError : public BaseError {
public:
    ParseError(const std::string& message, int lineIdx) : BaseError(
        "[Строка " + std::to_string(lineIdx) + "] " + std::string(message)
    ) {}
};

class MultipleUseError : public BaseError {
public:
    MultipleUseError(const std::string& message) : BaseError(message) {}
};

class ProgramError : public BaseError {
public:
    ProgramError(const std::string& message) : BaseError(message) {};
};

class CompiledProgramError : public BaseError {
public:
    CompiledProgramError(const std::string& message) : BaseError(message) {};
};

class EmptyStackError : public BaseError {
public:
    EmptyStackError(const std::string& message) : BaseError(message) {}
};

}