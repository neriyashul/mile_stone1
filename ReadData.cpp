#include "ReadData.h"

//Interpreter interpreter;
//ifstream infile;

void ReadData::read_Data_From_File(string fileName) {
    Interpreter interpreter;
    ifstream infile;

    // open file
    infile.open (fileName);

    // put content in string
    string input(dynamic_cast<stringstream const&>(stringstream() << infile.rdbuf()).str());

    // close file
    infile.close();

    // use lexer and interpreter
    //   interpreter.parser(interpreter.lexer(input));
}




void readFromConsole(){
    Interpreter interpreter;
    string input;
    string line;

    cout << "enter data (to finish type 'quitdata')" << endl;

    while (true) {
        // get line each time
        getline(cin, line);
        // read until type 'quit'
        if (line == "quitdata") { break; }
        // add '\n' after each line
        input += line + "\n";
    }

    // interpreter.parser(interpreter.lexer(input));


}