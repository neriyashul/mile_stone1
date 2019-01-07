//
// Created by neriya on 12/21/18.
//

#ifndef MILE_STONE1_COMMANDEXPRESSION_H
#define MILE_STONE1_COMMANDEXPRESSION_H

#include "Expression.h"
#include "Command.h"

class CommandExpression : public Expression {
    Command* command = nullptr;
    std::vector<std::string> arguments;
public:
    CommandExpression (Command* c, std::vector<std::string>& args) {
        command = c;
        arguments = args;
    }

    virtual ~CommandExpression() {
        delete command;
    }

    double calculate() override {
        command->doCommand(arguments);
        return 0;
    }

    Command* getCommand() const {
        return command;
    }
};
#endif //MILE_STONE1_COMMANDEXPRESSION_H
