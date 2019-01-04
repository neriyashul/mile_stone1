#include "Parser.h"
#include "PrintCommand.h"
#include "Equalize.h"


/**
* The function initialize the expressionMap.
*/
void Parser::initMap()  {
    expressionMap.insert(pair<string, int>("openDataServer", OPEN_SERVER));
    expressionMap.insert(pair<string, int>("connect", CONNECT));
    expressionMap.insert(pair<string, int>("var", VAR));
    expressionMap.insert(pair<string, int>("print", PRINT));
    expressionMap.insert(pair<string, int>("sleep", SLEEP));
    expressionMap.insert(pair<string, int>("=", EQUAL));
    expressionMap.insert(pair<string, int>("if", IF));
    expressionMap.insert(pair<string, int>("while", WHILE));
    expressionMap.insert(pair<string, int>("enterc", ENTERC));
    expressionMap.insert(pair<string, int>("exit", EXIT));
}


Command* Parser::createCommand(int expressNumInMap)  {

    switch (expressNumInMap) {
        case OPEN_SERVER:
            return new TcpServer(&numsOfPathsNames,
                    &valuesOfPathsNums, &mtxServer, notifier);
        case CONNECT:
            return new TcpClient(&this->isNewMassage,
                    &this->massage, &mtxClient, notifier);
        case VAR:
            return &dataVar;
        case PRINT:
            return new PrintCommand(&shuntYard, &variable);
        case SLEEP:
            return new SleepCommand(&shuntYard);
            case EQUAL:
                return new Equalize(&variable, shuntYard,
                         &this->isNewMassage, &this->massage, &mtxClient);
        case IF:
            return new IfCommand();
        case WHILE:
            return new WhileCommand();
        case ENTERC:
            return new Enterc();
        case EXIT:
            return new Exit();
        default:
            throw "problem with the input value";
    }
}



void Parser::callDoCommand(bool isCreateThread, Command *c,
              vector<thread> *threads, vector<string> &arg)  {
    if (isCreateThread) {
        // create thread of command->doCommand(arguments).
        threads->push_back(thread(&Command::doCommand,
                              c, ref(arg)));
        static bool isFirstTime = true;
        if (isFirstTime) {
            // wait until char is enter
            cout << "press some key to continue\n";
            Enterc e;
            e.doCommand(arg);
            isFirstTime = false;
        } else {
            // give a bit of time to the server or the client for connect.
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    } else {
        c->doCommand(arg);
    }
}


bool Parser::isScopeEnd(const string &str, int &numOfOpenerScope)  {
    if (str == STR_START_OF_SCOPE) { // if str = '{'
        ++numOfOpenerScope;
    } else if (str == STR_END_OF_SCOPE) {
        --numOfOpenerScope;
        // if open and close equal, close the scope.
        if (numOfOpenerScope == 0) { //str = '}'
            return true;
        }
    }
    return false;
}


void Parser::parse(vector<string> &vectorStr)  {
    bool isNewLine = true;
    bool isCreateThread = false;
    bool isInsideScope = false;
    int numOfOpenerScope = 0;
    Command *command = nullptr;
    vector<string> arguments;

    for (string &str : vectorStr) {
        // if new scope:
        if (isInsideScope) {
            if (isScopeEnd(str, numOfOpenerScope)) {
                isInsideScope = false;
                callDoCommand(isCreateThread, command, threads, arguments);
                isCreateThread = false;
            }
            arguments.push_back(str);

        } else if (str == STR_END_OF_LINE) {
              isNewLine = true;
              if (command != nullptr) {
                  callDoCommand(isCreateThread, command, threads, arguments);
                  isCreateThread = false;
                  arguments.clear();
              }
        } else if (isNewLine) { // str = first string in a line.

            // if there is command which creates threas.
            if (isCommandCreateThread(str)) {
                isCreateThread = true;
            } else if(isConditionCommand(str)) { // if condition command
                // create new scop.
                isInsideScope = true;
            }

            if (expressionMap.count(str) > 0) {
                command = createCommand(expressionMap[str]);
            } else { // if the command isn't in the first string.
                arguments.push_back(str);
                continue;
            }
            isNewLine = false;
        } else { // the argument in the middle of the line.
            arguments.push_back(str);
        }
    }
}

void Parser::end() {
    notifier.notifyAll();
    for (thread& t: *threads) {
        t.join();
    }
}