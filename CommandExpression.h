//
// Created by neriya on 12/21/18.
//

#ifndef MILE_STONE1_COMMANDEXPRESSION_H
#define MILE_STONE1_COMMANDEXPRESSION_H

#include "Expression.h"
#include "Command.h"

class CommandExpression : public Expression {
    Command* command;
    vector<string> arguments;
public:
    CommandExpression (Command* c) {
        command = c;
    }

    virtual double calculate() {
        command->doCommand(arguments);
    }

};
#endif //MILE_STONE1_COMMANDEXPRESSION_H