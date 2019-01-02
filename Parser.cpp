#include "Parser.h"


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
            return new TcpServer(&numsOfPathsNames, &valuesOfPathsNums, &mtxServer);
        case CONNECT:
            return new TcpClient();
            case VAR:
                return &dataVar;
            /*case PRINT:
                return new PrintCommand();
            case SLEEP:
                return new SleepCommand();
            case EQUAL:
                return new EqualCommand();*/
        case IF:
            return new IfCommand();
        case WHILE:
            return new WhileCommand();
        case ENTERC:
            return new Enterc();
        case EXIT:
            return new Exit();
        default:
            return nullptr;
    }
}



void Parser::callDoCommand(bool isCreateThread, Command *c,
              vector<thread> &threads, vector<string> &arg)  {
    if (isCreateThread) {
        // create thread of command->doCommand(arguments).
        threads.push_back(thread(&Command::doCommand,
                              c, ref(arg)));
        static bool isFirstTime = true;
        if (isFirstTime) {
            // wait until char is enter
            Enterc e;
            e.doCommand(arg);
            isFirstTime = false;
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
    vector<thread> threads;

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
              }
        } else if (isNewLine) { // str = first string in a line.

            // if there is command which creates threas.
            if (isCommandCreateThread(str)) {
                isCreateThread = true;
            } else if(isConditionCommand(str)) { // if condition command
                // create new scop.
                isInsideScope = true;
            }

            // create new command according to the command in the line.
            command = createCommand(expressionMap.at(str));
            // if the first string in the
            if (command == nullptr) {
                // continue; **********************************************
            }
            isNewLine = false;
        } else { // the argument in the middle of the line.
            arguments.push_back(str);
        }
    }
}