//
// Created by yedaya on 12/25/18.
//


#include "ReadData.h"

void ReadData::readFromFile(string fileName) {
    Interpreter interpreter;
    ifstream infile;

    // open file
    infile.open (fileName);

    // put content in string
    string input(dynamic_cast<stringstream const&>(stringstream() << infile.rdbuf()).str());

    // close file
    infile.close();

    // use lexer and interpreter
    interpreter.parse(interpreter.lexer(input));
}

void ReadData::readFromConsole() {
    Interpreter interpreter;
    string input;
    string line;

    cout << "type your code (to finish type 'exit')" << endl;

    unsigned numOfOpenScope = 0;
    unsigned numOfCloseScope = 0;
    while (true) {
        // get line each time
        getline(cin, line);

        // read until type 'quit'
        if (line == "exit") { break; }

        // if in the new line there is new scope add it.
        if (line.find_first_of('{') != string::npos) {
            ++numOfOpenScope;
        // if in the new line there is end of scope add it.
        } else if (line.find_first_of('}') != string::npos) {
            ++numOfCloseScope;
        }

        // add '\n' after each line
        input += line + "\n";

        // if there is open scope, continue to read.
        if (numOfOpenScope != numOfCloseScope) {
            continue;
        }

        // use lexer and interpreter
        interpreter.parse(interpreter.lexer(input));
    }
}