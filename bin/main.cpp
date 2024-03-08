#include <iostream>
#include "parser.hpp"


int main() {
    using namespace std;
    using namespace vm;

    Parser parser;
    Program program = parser.parseProgram("data/programs/program2.txt");

    return 0;
}