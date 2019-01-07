#include "WhileCommand.h"

void WhileCommand::doCommand(std::vector<std::string> &v)  {
    if (v.empty()) {
        throw "wrong numbers of arguments";
    }
    conditionCreator(v);

    while (isConditionSatisfy()) {
        for(Expression* e: arguments) {
            e->calculate();
        }
    }
}