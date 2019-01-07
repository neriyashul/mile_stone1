#ifndef MILE_STONE1_IFCOMMAND_H
#define MILE_STONE1_IFCOMMAND_H


#include "ConditionParserCommand.h"

class IfCommand : public ConditionParserCommand {
public:
    explicit IfCommand(ExpressionFactory* expressFactor)
           : ConditionParserCommand(expressFactor) {}
    void doCommand(std::vector<std::string>& v) override;
};

#endif //MILE_STONE1_IFCOMMAND_H
