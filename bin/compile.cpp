#include <iostream>
#include "parser.hpp"

int main(int argc, char *argv[]) {
    using namespace std;
    using namespace vm;

    string from = "data/programs/default.txt";
    string to = "program.bin";
    if (argc > 1) {
        from = argv[1];
    }
    if (argc > 2) {
        to = argv[2];
    }

    Program program = Parser::parseProgram(from);
    program.save(to);

    return 0;
}