#ifndef MILE_STONE1_CONDITIONPARSER_H
#define MILE_STONE1_CONDITIONPARSER_H

#include "Command.h"
#include <vector>
#include "Expression.h"


class ConditionParserCommand : public Command {
protected:
    vector<Command*> commands;
public:

    /**
 * The function gets 2 Expressions and condition.
 *         and return if the condition is satisfy.
 *
 * The condition are:
 * 1) !=
 * 2) ==
 * 3) <=
 * 4) >=
 * 5) <
 * 6) >
 *
 * @param condition - const char*
 * @param exp1 - Expression.
 * @param exp2 - Expression.
 * @return bool.
 */
 bool isConditionSatisfy(const char* condition, Expression& exp1, Expression& exp2);

 /**
  * @overrite doCommand.
  */
 virtual void doCommand(vector<string>&) = 0;

 /**
  * The function insert command to commands.
  * @param command
  */
 void addCommand(Command* command) {
     commands.push_back(command);
 }
};


#endif //MILE_STONE1_CONDITIONPARSER_H
