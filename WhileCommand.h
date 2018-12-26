#ifndef MILE_STONE1_WHILE_H
#define MILE_STONE1_WHILE_H

#include <string.h>
#include "ConditionParserCommand.h"


class WhileCommand : public ConditionParserCommand {
public:
    virtual void doCommand(const vector<string>& v) {
        vector<vector<string>> condVec = createConditionVec(v);

        string l = combineStrings(condVec[0]);
        string r = combineStrings(condVec[2]);
        Expression* left = expFromShuntingYard(l);
        Expression* right = expFromShuntingYard(r);
        string oper = combineStrings(condVec[1]);


        while (isConditionSatisfy(oper.c_str(), left, right)) {
            callToParser();
        }
    }
};


#endif //MILE_STONE1_WHILE_H
