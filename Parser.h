#ifndef MILE_STONE1_PARSER_H
#define MILE_STONE1_PARSER_H

#include "map"
#include "Expression.h"
using namespace std;

typedef struct {
    bool isCanBeMoreArg = false;
    int argumentNum;
    Expression* express;
} ExpressionDetail;

map<string, ExpressionDetail> expressionMap;
class Parser  {

    static void initMap() {
        ExpressionDetail e;
        e.argumentNum = 3;
        e.isCanBeMoreArg = true;
        e.express = new ;
        expressionMap.insert("while", e);
    }


    Parser(int args, char** argv) {
        initMap(args);
    }

};

#endif //MILE_STONE1_PARSER_H
