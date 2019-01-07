#include "Parser.h"
#include "PrintCommand.h"
#include "Equalize.h"

using namespace std;


Parser::Parser(std::vector<std::thread> *thread,
               std::unordered_map<std::string, int>* numsOfNames,
               std::unordered_map<int, double*>* valuesPaths,
               std::unordered_map<std::string,Var*>* vars,
               std::mutex* mutexServer,
               std::mutex* mutexClient,
               Notifier* noti) {
    this->variable = vars;
    this->threads = thread;
    this->numsOfPathsNames = numsOfNames;
    this->valuesOfPaths = valuesPaths;
    this->mtxServer = mutexServer;
    this->mtxClient = mutexClient;
    this->notifier = noti;
    this->expressFactor = new ShuntingYard(variable);
    this->dataVar = new VarDataCommand(numsOfPathsNames,
                                       valuesOfPaths, variable, mtxServer, expressFactor);
    initMap();
}


Parser::~Parser() {
    delete(this->expressFactor);
    delete(this->dataVar);
}



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


ConditionParserCommand* Parser::createConditionCommand(int expressNumInMap) {
    switch (expressNumInMap) {
        case IF:
            return new IfCommand(this->expressFactor);
        case WHILE:
            return new WhileCommand(this->expressFactor);
        default:
            throw "problem with the input value";
    }
}

Command* Parser::createCommand(int expressNumInMap)  {

    switch (expressNumInMap) {
        case OPEN_SERVER:
            return new TcpServer(numsOfPathsNames,
                    valuesOfPaths, mtxServer, notifier,
                                       threads, expressFactor);
        case CONNECT:
            return new TcpClient(&this->isNewMassage,
                    &this->massage, mtxClient, notifier, threads, expressFactor);
        case VAR:
            return new VarDataCommand(numsOfPathsNames,
                                      valuesOfPaths, variable, mtxServer, expressFactor);
        case PRINT:
            return new PrintCommand(expressFactor, variable);
        case SLEEP:
            return new SleepCommand(expressFactor);
            case EQUAL:
                return new Equalize(variable, expressFactor,
                         &this->isNewMassage, &this->massage, mtxClient);
        case ENTERC:
            return new Enterc();
        case EXIT:
            return new Exit();
        default:
            throw "unrecognized Command";
    }
}



bool Parser::isOneScopeEnd(const vector<string>& line)  {
    auto it = std::find(line.begin(), line.end(), STR_END_OF_SCOPE);
    return  (it != line.end());
}



vector<string> Parser::getOneLine(unsigned long index, vector<string> &vectorStr) {
    vector<string> line;
    for (unsigned long i = index; i < vectorStr.size(); ++i) {
        if (vectorStr[i] == STR_END_OF_LINE) {
            return line;
        } else {
            line.push_back(vectorStr[i]);
        }
    }
    return line;
}


Command* Parser::parseOneLine(vector<string>* arguments) {

    Command *command = nullptr;

    string commandName;
    // if the command is in the first string:
    if (expressionMap.count((*arguments)[0]) > 0) {
        commandName = (*arguments)[0];
        arguments->erase(arguments->begin());
    } else if (arguments->size() > 1){
        commandName = (*arguments)[1];
        arguments->erase(arguments->begin()+1);
    }
    if (commandName.empty()) {
        return nullptr;
    }
    command = createCommand(expressionMap[commandName]);


    return command;
}

vector<Expression*> Parser::parse(vector<string> &vectorStr)  {
    static unsigned long vecIndex = 0;
    vector<string> line;
    vector<Expression*> expressions;


    while (vecIndex < vectorStr.size()) {
        line = getOneLine(vecIndex, vectorStr);
        vecIndex += line.size() + 1; // +1 for the ';'

        Command *command;
        if(isConditionCommand(line[0])) {
            ConditionParserCommand* c;
            c = createConditionCommand(expressionMap[line[0]]);

            c->setExpressionArgs(parse(vectorStr));
            command = c;

            line.erase(line.begin()); // delete command string.
        } else {
            command = parseOneLine(&line);
        }

        if (command) {
            expressions.push_back(new CommandExpression(command, line));
        }

        if (isOneScopeEnd(line)) {
            return expressions;
        }

        line.clear();
    }

    return  expressions;
}


void Parser::end() {
    notifier->notifyAll();
    for (thread& t: *threads) {
        t.join();
    }
}