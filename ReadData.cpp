
#include "ReadData.h"

using  namespace std;
void ReadData::readFromFile(string fileName) {

    RunProgram runable;
    ifstream infile;

    // open file
    infile.open (fileName);

    // put content in string
    string input(dynamic_cast<stringstream const&>(
                 stringstream() << infile.rdbuf()).str());

    // close file
    infile.close();

    runable.run(input);
}

void ReadData::readFromConsole() {
    RunProgram runable;

    string input;
    string line;

    cout << "type your code (to finish type 'exit')" << endl;

    unsigned numOfOpenScope = 0;
    unsigned numOfCloseScope = 0;
    while (true) {
        // get line each time
        getline(cin, line);

        // read until type 'quit'
        if (line == "exit") {
            break;
        }

        // if in the new line there is new scope add it.
        if (line.find('{') != string::npos) {
            ++numOfOpenScope;
        // if in the new line there is end of scope add it.
        } else if (line.find('}') != string::npos) {
            ++numOfCloseScope;
        }

        // add '\n' after each line
        input += line + "\n";

        // if there is open scope, continue to read.
        if (numOfOpenScope != numOfCloseScope
                           || runable.isContinue(line)) {
            continue;
        }
        runable.run(input);
    }
}