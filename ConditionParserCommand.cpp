#include "ConditionParserCommand.h"

using namespace std;

/**
 * The function return if the condition satisfy.
 *
 * The condition are:
 * 1) !=
 * 2) ==
 * 3) <=
 * 4) >=
 * 5) <
 * 6) >
 * 7) !
 * 8) none (no condition) - return exp1->calculate
 *
 * @param condition - const char*
 * @param exp1 - Expression.
 * @param exp2 - Expression.
 * @return bool.
 */
bool ConditionParserCommand::isConditionSatisfy() {

    // if there is no condition - return exp1->calc.
    if (this->conditionOperator.empty()){
        return (bool) left->calculate();
    }
    // if there is 2 char in the condition:
    if (conditionOperator.size() > 1 && conditionOperator[1] == '=') {
        switch (conditionOperator[0]) {
            // case !=
            case '!':
                return (left->calculate() != right->calculate());
                // case <=
            case '<':
                return (left->calculate() <= right->calculate());
                // case ==
            case '=':
                return (left->calculate() == right->calculate());
                // case >=
            case '>':
                return (left->calculate() >= right->calculate());
            default:
                return false;
        }
    } else {
        switch(conditionOperator[0]) {
            case '<':
                return (left->calculate() < right->calculate());
            case'>':
                return (left->calculate() > right->calculate());
            case '!':
                return !(bool)left->calculate();
            default:
                return false;
        }
    }
}

int ConditionParserCommand::getOperatorLocation(vector<string>& v) {
    for (int i = 0; i < v.size(); ++i) {
        if(this->expressionFactory
                ->isConditionOperator(v[i])) {
            return i;
        }
    }
    return -1;
}


void ConditionParserCommand::
              conditionCreator(vector<string>& v) {
    int i = getOperatorLocation(v);
    if (i != -1) {
        this->conditionOperator = v[i];
    }
    vector<Expression*>expressions = this->expressionFactory
                                         ->expressionFromString(v);
    unsigned long size = expressions.size();
    if (size > 0) {
        this->left = expressions[0];
    } else {
        throw "wrong numbers of arguments";
    }

    if(size > 1) {
        this->right = expressions[1];
    }
}