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
#include "VarDataCommand.h"
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
    unordered_map<string, int> numsOfPathsNames = {
            {"/instrumentation/airspeed-indicator/indicated-speed-kt", 1},
            {"/instrumentation/altimeter/indicated-altitude-ft", 2},
            {"/instrumentation/altimeter/pressure-alt-ft", 3},
            {"/instrumentation/attitude-indicator/indicated-pitch-deg", 4},
            {"/instrumentation/attitude-indicator/indicated-roll-deg", 5},
            {"/instrumentation/attitude-indicator/internal-pitch-deg", 6},
            {"/instrumentation/attitude-indicator/internal-roll-deg", 7},
            {"/instrumentation/encoder/indicated-altitude-ft", 8},
            {"/instrumentation/encoder/pressure-alt-ft", 9},
            {"/instrumentation/gps/indicated-altitude-ft", 10},
            {"/instrumentation/gps/indicated-ground-speed-kt", 11},
            {"/instrumentation/gps/indicated-vertical-speed", 12},
            {"/instrumentation/heading-indicator/indicated-heading-deg", 13},
            {"/instrumentation/magnetic-compass/indicated-heading-deg", 14},
            {"/instrumentation/slip-skid-ball/indicated-slip-skid", 15},
            {"/instrumentation/turn-indicator/indicated-turn-rate", 16},
            {"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 17},
            {"/controls/flight/aileron", 18},
            {"/controls/flight/elevator", 19},
            {"/controls/flight/rudder", 20},
            {"/controls/flight/flaps", 21},
            {"/controls/engines/engine/throttle", 22},
            {"/engines/engine/rpm" ,23}};
    /*
     * the map save the value in path from the previous map.
     */
    unordered_map<int, double> valuesOfPathsNums = {{1,0}, {2,0},{3,0}, {4,0},{5,0}, {6,0},{7,0}, {8,0},
                                              {9,0}, {10,0},{11,0},{12,0},{13,0},{14,0},{15,0},
                                              {16,0},{17,0},{18,0},{19,0}, {20,0},{21,0},{22,0},{23,0}};
    unordered_map<string, int> expressionMap;

    std::unordered_map<std::string,Var*> variable;
    VarDataCommand dataVar;
    mutex mtxServer;
    mutex mtxClient;
    ShuntingYard shuntYard;
    bool isNewMassage = false;
    string massage;
    vector<thread>* threads = nullptr;
    Notifier notifier;

public:

    explicit Parser(vector<thread>* threadsVec) : dataVar(&numsOfPathsNames,
                &valuesOfPathsNums, &variable, &mtxServer), shuntYard(&variable) {
        threads = threadsVec;
        initMap();
    }

    ~Parser(){
        for (std::pair<string, Var*> p : variable) {
            if (p.second != nullptr) {
                delete(p.second);
            }
        }
    }

    /**
     * return wheter or not exist the insert str in conditionMap.
     * i.e if it is operator.
     * @param oper - string&.
     * @return bool.
     */
    bool isOperator(string& oper) const {
        return (bool) expressionMap.count(oper);
    }

    /**
    * The function initialize the expressionMap.
    */
    void initMap();

    Command* createCommand(int expressNumInMap);

    /**
     * the function return if string is some condition comman:
     * if/while
     */
    bool isConditionCommand(string& str) {
        return  (str == "if" || str == "while");
    }

    bool isCommandCreateThread(string& str) {
        return  (str == "openDataServer" || str == "connect");
    }


    void callDoCommand(bool isCreateThread, Command* c,
            vector<thread>* threads, vector<string>& arg);

    bool isScopeEnd(const string& str, int& numOfOpenerScope);


    /**
     * the function parse every line in some vector that insert
     *                          and call to commands in accordance.
     * @param vectorStr - vector<string>&.
     */
    void parse(vector<string>& vectorStr);

    /**
     * the function call no all listener to close the threads.
     */
    void end();
};

#endif //MILE_STONE1_THEPARSER_H