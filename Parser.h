#ifndef MILE_STONE1_PARSER_H
#define MILE_STONE1_PARSER_H

#include <unordered_map>
#include "Expression.h"
#include "WhileCommand.h"
#include "CommandExpression.h"
using namespace std;

class Parser  {

    unordered_map<string, int> expressionMap;

public:

    Parser() {
        initMap();
    }

    /**
     * The funcion create new Expression and return it.
     *
     * @param nameOperation - string.
     * @return Expression&.
     */
    Expression& parse(string nameOperation) {
        int numInMap = expressionMap.at(nameOperation);
        switch (numInMap) {
            case 1:
                return new CommandExpression(new OpenServerCommand());
            case 2:
                return new CommandExpression(new OpenClientCommand());
            case 3:
                return new CommandExpression(new Var());
            case 4:
                return new CommandExpression(new PrintCommand());
            case 5:
                return new CommandExpression(new SleepCommand());
            case 6:
                return new CommandExpression(new EqualCommand());
            case 7:
                return new CommandExpression(new IfCommand());
            case 8:
                return new CommandExpression(new WhileCommand());
            default:
                throw "invalid operaiton";
        }
    }

    /**
     * The function initialize the expressionMap.
     */
    void initMap() {
        expressionMap.insert(pair<string, int> ("openDataServer", 1));
        expressionMap.insert(pair<string, int> ("connect", 2));
        expressionMap.insert(pair<string, int> ("var", 3));
        expressionMap.insert(pair<string, int> ("print", 4));
        expressionMap.insert(pair<string, int> ("sleep", 5));
        expressionMap.insert(pair<string, int> ("=", 6));
        expressionMap.insert(pair<string, int> ("if", 7));
        expressionMap.insert(pair<string, int> ("while", 8));
    }




};

#endif //MILE_STONE1_PARSER_H
