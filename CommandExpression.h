//
// Created by neriya on 12/21/18.
//

#ifndef MILE_STONE1_COMMANDEXPRESSION_H
#define MILE_STONE1_COMMANDEXPRESSION_H

#include "Expression.h"
#include "Command.h"

class CommandExpression : public Expression {
    Command* command;
    std::vector<std::string> arguments;
public:
    CommandExpression (Command* c) {
        command = c;
    }

    ~CommandExpression() {
        delete command;
    }

    virtual double calculate() {
        command->doCommand(arguments);
        return 0;
    }

};
#endif //MILE_STONE1_COMMANDEXPRESSION_H
