//
// Created by neriya on 12/26/18.
//

#ifndef MILE_STONE1_IFCOMMAND_H
#define MILE_STONE1_IFCOMMAND_H


#include "ConditionParserCommand.h"

class IfCommand : public ConditionParserCommand {
public:
    virtual void doCommand(const vector<string>& v) {
        vector<string> condVec = createConditionVec(v);

        Expression* left = expFromShuntingYard(condVec[0]);
        Expression* right = expFromShuntingYard(condVec[2]);

        if (isConditionSatisfy(condVec[1].c_str(), left, right)) {
            callToParser();
        }
    }
};



#endif //MILE_STONE1_IFCOMMAND_H
