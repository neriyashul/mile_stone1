#ifndef MILE_STONE1_IFCOMMAND_H
#define MILE_STONE1_IFCOMMAND_H


#include "ConditionParserCommand.h"

class IfCommand : public ConditionParserCommand {
public:
    virtual void doCommand(vector<string>& v) {
        vector<string> strVec = conditionHandle(v);

        Expression* left = expFromShuntingYard(strVec[0]);
        Expression* right = expFromShuntingYard(strVec[2]);

        if (isConditionSatisfy(strVec[1], left, right)) {
            callToParser();
        }
    }
};



#endif //MILE_STONE1_IFCOMMAND_H
