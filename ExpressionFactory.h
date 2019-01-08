
#ifndef MILE_STONE1_EXPRESSIONFACTORY_H
#define MILE_STONE1_EXPRESSIONFACTORY_H

#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include "Expression.h"
#include "MathExpressions.h"
#include "Var.h"
#include "Num.h"

#define STR_OF_BINARY_OPERATOR "+-/*"

class ExpressionFactory {


    std::unordered_map<std::string,Var*>* variables;

protected:
    enum priorityOperator {
        openBracket, add, sub = add, mul, divide = mul
    };


    /**
     * The function gets a map and add it operator and there priority.
     * @param priorityMap - map.
     */
    void addPriorityOperator(std::map<char, priorityOperator> &priorityMap);



    /**
     * The function return if the string is binary expression.
     *
     */
    bool isBinaryOperator(unsigned, std::string&);


    /**
     * The function return new binary Expression according to insert string.
     * @param oper - string&.
     * @param exp1 - Expression*.
     * @param exp2 - Expression*.
     * @return Expression*.
     */
    Expression *createBinabryExpression(std::string &oper, Expression *exp1, Expression *exp2);

    /**
     * The function return if the string that insert is number.
     * @param strExpression - string&.
     * @return bool.
     */
    bool isDoubleNumber(const std::string &);


    /**
     * The function gets deque with strings of expressions
     * in postfix oprder and return Expression in accordance.
     *
     * @param strExpressions - deque<string>.
     * @return Expression*.
     */
    Expression* postfixCalculator(std::deque<std::string> strExpressions);


    /**
     * the function get vector of string and return vector of
     * vectors divided by the end of the expressions.
     *
     * @param argument vector<std::string>
     * @return vector<vector<string>>.
     */
    std::vector<std::vector<std::string>> divideToExpressions(
            std::vector<std::string> &argument);


public:

    virtual ~ExpressionFactory() = default;
    explicit ExpressionFactory(std::unordered_map<std::string,Var*>* vars) {
        variables = vars;
    }

    /**
     * the function return if the enter string is a name of variable.
     * @param name - string&.
     * @return bool.
     */
    bool isVar(std::string& name) {
        return (variables->count(name) > 0);
    }

    /**
 * the function return if the insert char is condition operator.
 * @param c - char
 * @return bool.
 */
    bool isConditionOperator (std::string& s);


    /**
     * The function gets a string of expression and return Expression in accordance.
     * @param strExpress - string&.
     * @return Expression*.
     */
    virtual std::vector<Expression*> expressionFromString(std::vector<std::string>& expression) = 0;







};


#endif //MILE_STONE1_EXPRESSIONFACTORY_H
