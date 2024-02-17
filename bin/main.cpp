#include <iostream>
#include "stack.hpp"

int main() {
    using namespace std;
    using namespace vm;

    Stack<size_t> s1;
    for (int i = 0; i < 10; i++) {
        s1.push(i);
    }

    Stack<size_t> s2(s1);
    int i = 9;
    while (!s2.empty()) {
        s2.pop();
        i--;
    }

    Stack<size_t> s3(std::move(s2));

    s3 = s1;

    s3.pop();
    s1 = std::move(s3);
    s3.clear();

    s1 = s1;
    s1 = std::move(s1);

    Stack<size_t> s4 = Stack<size_t>();
    for (int i = 0; i < 100; i++) {
        s4.push(i);
    }

    s4 = s1;
    
    return 0;
}