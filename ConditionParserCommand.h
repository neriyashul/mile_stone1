#include <utility>

#ifndef MILE_STONE1_CONDITIONPARSERCOMMAND_H
#define MILE_STONE1_CONDITIONPARSERCOMMAND_H

#include "Command.h"
#include <vector>
#include <cstring>
#include "Expression.h"
#include "ExpressionFactory.h"
#include "ShuntingYard.h"

#define STR_END_OF_CONDITION "{"
#define STR_START_OF_SCOPE "{"
#define STR_END_OF_SCOPE "}"



class ConditionParserCommand : public Command {
    ExpressionFactory* expressionFactory;
protected:
    std::vector<Expression*> arguments;
    Expression* left = nullptr;
    Expression* right = nullptr;
    std::string conditionOperator;
public:
    explicit ConditionParserCommand(ExpressionFactory* expressFactor) {
        expressionFactory = expressFactor;
    }

    ~ConditionParserCommand() override {
        delete left;
        delete right;

        for (Expression* e: arguments) {
            delete(e);
        }
    }

  /**
   * add argument to the vector.
   * @param Expression*.
   */
    void setExpressionArgs(std::vector<Expression*> e) {
        this->arguments = std::move(e);
    }

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
 * 7) !
 * 8) none
 *
 * @param condition - const char*
 * @param exp1 - Expression.
 * @param exp2 - Expression.
 * @return bool.
 */
 bool isConditionSatisfy();


 /**
  * @overrite doCommand.
  */
 virtual void doCommand(std::vector<std::string>&) = 0;

    /**
     * the function return the location of the operator in the vector.
     * @param v - vector<string>&.
     * @return int.
     */
    int getOperatorLocation(std::vector<std::string>& );

    /**
        * the function handle to condition and return vector of string with:
        * 1) left size of the operator in the condition.
        * 2) operator
        * 3) right size of the operator in the condition.
        * @param v - vector<string>.
        * @return vector<string>.
        */
    void conditionCreator(std::vector<std::string>& v);

};


#endif //MILE_STONE1_CONDITIONPARSER_H
