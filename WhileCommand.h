#ifndef MILE_STONE1_WHILE_H
#define MILE_STONE1_WHILE_H

#include "ConditionParserCommand.h"
#include "Parser.h"

class WhileCommand : public ConditionParserCommand {
    vector<string> arguments;
public:
    WhileCommand() {

    }

    void addArgument(string& arg) {
        arguments.push_back(arg);
    }

    virtual void doCommand(vector<string>&) {

    }
};


#endif //MILE_STONE1_WHILE_H
