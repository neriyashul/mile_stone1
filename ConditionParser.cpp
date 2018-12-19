#include "ConditionParser.h"
#include "string.h"


/**
 * The function gets 2 Expressions and condition.
 *           and return if the condition satisfy.
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
bool ConditionParser::isConditionSatisfy(
        const char* condition, Expression& exp1, Expression& exp2) {

    // if there is 2 char in the condition:
    if (condition[1] == '=') {
        switch (condition[0]) {
            // case !=
            case '!':
                return (exp1 != exp2);
                // case <=
            case '<':
                return (exp1 <= exp2);
                // case ==
            case '=':
                return (exp1 == exp2);
                // case >=
            case '>':
                return (exp1 >= exp2);
            default:
                return false;
        }
    } else {
        if (condition[0] == '<') {
            return (exp1 < exp2);
        } else if (condition[0] == '>') {
            return (exp1 > exp2);
        }

        return false;
    }
}
