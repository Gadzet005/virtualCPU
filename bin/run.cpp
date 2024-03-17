#include <iostream>
#include "processor.hpp"

int main(int argc, char *argv[]) {
    using namespace std;
    using namespace vm;

    string path = "program.bin";
    if (argc > 1) {
        path = argv[1];
    }

    Processor processor;
    Program program = Program::load(path);
    processor.executeProgram(program);

    return 0;
}