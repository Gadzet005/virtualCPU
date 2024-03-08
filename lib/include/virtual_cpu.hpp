#pragma once
#include "stack.hpp"

namespace vm {

class VirtualCPU {
public:
    Stack<int> stack;
};

}
