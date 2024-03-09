#include <iostream>
#include "parser.hpp"
#include "processor.hpp"


int main() {
    using namespace std;
    using namespace vm;

    Parser parser;
    Processor processor;
    Program program = parser.parseProgram("data/programs/program2.txt");
    processor.executeProgram(program);

    return 0;
}