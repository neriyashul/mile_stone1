//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_THEPARSER_H
#define MILE_STONE1_THEPARSER_H



#include "Expression.h"
#include "CommandExpression.h"

#include "SleepCommand.h"


#include "TcpClient.h"
#include "TcpServer.h"
#include "Enterc.h"
#include "Exit.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "VarCreatorCommand.h"
#include "Notifier.h"
#include <unordered_map>
#include <cstring>
#include <thread>

enum {
    OPEN_SERVER, CONNECT, VAR, PRINT, SLEEP, EQUAL, IF, WHILE, ENTERC, EXIT
};

#define STR_END_OF_LINE ";"


class Parser {

    /*  create map that every path has the next num after the previous,
        accordingly tp the order in the xml file. */
    std::unordered_map<std::string, int>* numsOfPathsNames;
    /*
     * the map save the value in path from the previous map.
     */

    bool isNewMassage = false;
    std::string massage;
    std::unordered_map<int, double*>* valuesOfPaths;
    std::unordered_map<std::string,Var*>* variable;
    std::mutex* mtxServer;
    std::mutex* mtxClient;
    ExpressionFactory* expressFactor;
    std::vector<std::thread>* threads = nullptr;
    Notifier* notifier;
    VarDataCommand* dataVar;
    std::unordered_map<std::string, int> expressionMap;

public:
    Parser(std::vector<std::thread> *thread,
           std::unordered_map<std::string, int>* numsOfNames,
           std::unordered_map<int, double*>* valuesPaths,
           std::unordered_map<std::string,Var*>* vars,
           std::mutex* mutexServer,
           std::mutex* mutexClient,
           Notifier* noti
    );
    ~Parser();

    /**
     * return wheter or not exist the insert str in conditionMap.
     * i.e if it is operator.
     * @param oper - string&.
     * @return bool.
     */
    bool isOperator(std::string& oper) const {
        return (bool) expressionMap.count(oper);
    }

    /**
    * The function initialize the expressionMap.
    */
    void initMap();

    /**
     * the function return new ConditionParserCommand
     * in accordance to the inserted int.
     *
     * @return -  ConditionParserCommand*.
     */
    ConditionParserCommand* createConditionCommand(int);

    /**
     * the function return new Command
     * in accordance to the inserted int.
     *
     * @return -  Command*.
     */
    Command* createCommand(int);

    /**
     * the function return if string is some condition comman:
     * if/while
     */
    bool isConditionCommand(std::string& str) {
        return  (str == "if" || str == "while");
    }

    std::vector<std::string> getOneLine(unsigned long index, std::vector<std::string> &vectorStr);

    /*void callDoCommand(bool isCreateThread, Command* c,
            vector<thread>* threads, vector<string>& arg);
            */

    bool isOneScopeEnd(const std::vector<std::string>&);


    Command* parseOneLine(std::vector<std::string>*);

    /**
     * the function parse every line in some vector that insert
     *                          and call to commands in accordance.
     * @param vectorStr - vector<string>&.
     */

    std::vector<Expression*> parse(std::vector<std::string> &vectorStr);

    /**
     * the function call no all listener to close the threads.
     */
    void end();
};

#endif //MILE_STONE1_THEPARSER_H
