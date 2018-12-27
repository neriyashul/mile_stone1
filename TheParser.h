//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_THEPARSER_H
#define MILE_STONE1_THEPARSER_H



#include "Expression.h"
#include "CommandExpression.h"

#include "SleepCommand.h"


#include "OpenTcpClientCommand.h"
#include "OpenTcpServer.h"
#include "Enterc.h"
#include "Exit.h"

#include <unordered_map>
#include <string.h>
#include <thread>

using namespace std;

#define STR_END_OF_LINE ";"

class ConditionParserCommand;

class Parser {
    unordered_map<string, int> expressionMap;
   /* vector <string> names = {"/instrumentation/airspeed-indicator/indicated-speed-kt",
                             "/instrumentation/altimeter/indicated-altitude-ft",
                             "/instrumentation/altimeter/pressure-alt-ft",
                             "/instrumentation/attitude-indicator/indicated-pitch-deg",
                             "/instrumentation/attitude-indicator/indicated-roll-deg",
                             "/instrumentation/attitude-indicator/internal-pitch-deg",
                             "/instrumentation/attitude-indicator/internal-roll-deg",
                             "/instrumentation/encoder/indicated-altitude-ft",
                             "/instrumentation/encoder/pressure-alt-ft",
                             "/instrumentation/gps/indicated-altitude-ft",
                             "/instrumentation/gps/indicated-ground-speed-kt",
                             "/instrumentation/gps/indicated-vertical-speed",
                             "/instrumentation/heading-indicator/indicated-heading-deg",
                             "/instrumentation/magnetic-compass/indicated-heading-deg",
                             "/instrumentation/slip-skid-ball/indicated-slip-skid",
                             "/instrumentation/turn-indicator/indicated-turn-rate",
                             "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                             "/controls/flight/aileron",
                             "/controls/flight/elevator",
                             "/controls/flight/rudder",
                             "/controls/flight/flaps",
                             "/controls/engines/engine/throttle",
                             "/engines/engine/rpm"}; */

public:

    Parser() {
        initMap();
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
    void initMap() {
        expressionMap.insert(pair<string, int>("openDataServer", 1));
        expressionMap.insert(pair<string, int>("connect", 2));
        expressionMap.insert(pair<string, int>("var", 3));
        expressionMap.insert(pair<string, int>("print", 4));
        expressionMap.insert(pair<string, int>("sleep", 5));
        expressionMap.insert(pair<string, int>("=", 6));
        expressionMap.insert(pair<string, int>("if", 7));
        expressionMap.insert(pair<string, int>("while", 8));
        expressionMap.insert(pair<string, int>("enterc", 9));
    }

    Command* createCommand(int expressNumInMap) {
        switch (expressNumInMap) {
            case 1:
                return new OpenTcpServer();
            case 2:
                return new OpenTcpCommand();
          /*  case 3:
                return Var();
            case 4:
                return new PrintCommand();
            case 5:
                return new SleepCommand();
            case 6:
                return new EqualCommand();
            case 7:
                return new IfCommand();
            case 8:
                return new WhileCommand();
            */case 9:
                return new Enterc();
            case 10:
                return new Exit();
            default:
                throw "invalid operation";
        }
    }


    void parse(vector<string>& vectorStr) {
        int sockfd = -1;
        bool isNewLine = true;
        Command *command = nullptr;
        vector<string> arguments;

        for (string &str : vectorStr) {

            if (isNewLine) {
                // create new command according to the command in the line.
                command = createCommand(expressionMap.at(str));
                isNewLine = false;
            } else {
                arguments.push_back(str);
            }

            if (!strcmp(str.c_str(),STR_END_OF_LINE) && command != nullptr) {
                isNewLine = true;
                command->doCommand(arguments);
            }
        }
    }
};


#endif //MILE_STONE1_THEPARSER_H
