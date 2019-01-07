#include "IfCommand.h"

void IfCommand::doCommand(std::vector<std::string> &v)  {
    if (v.empty()) {
        throw "wrong numbers of arguments";
    }
    conditionCreator(v);

    if (isConditionSatisfy()) {
        for(Expression* e: arguments) {
            e->calculate();
        }
    }
}