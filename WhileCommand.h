#ifndef MILE_STONE1_WHILE_H
#define MILE_STONE1_WHILE_H

#include "ConditionParserCommand.h"
#include <cstring>

class WhileCommand : public ConditionParserCommand {
public:
    explicit WhileCommand(ExpressionFactory* expressFactor)
            : ConditionParserCommand(expressFactor) {}

    void doCommand(std::vector<std::string>& v) override;
};


#endif //MILE_STONE1_WHILE_H
