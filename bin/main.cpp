#include <iostream>
#include "parser.hpp"
#include "processor.hpp"

int main(int argc, char *argv[]) {
    using namespace std;
    using namespace vm;

    std::string path = "data/programs/default.txt";
    if (argc > 1) {
        path = argv[1];
    }

    Processor processor;
    Program program = Parser::parseProgram(path);
    processor.executeProgram(program);

    return 0;
}