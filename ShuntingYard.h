#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include "Expression.h"
#include "AddExp.h"
#include "MulExp.h"
#include "DivExp.h"
#include "MinusExp.h"
#include "Num.h"


using namespace std;


class ShuntingYard {

    enum priorityOperator {
        openBracket, add, sub = add, mul, divide = mul
    };


    /**
     * The function gets a map and add it operator and there priority.
     * @param priorityMap - map.
     */
    void addPriorityOperator(map<char, priorityOperator> &priorityMap) {
        priorityMap.insert(pair<char, priorityOperator>('+', add));
        priorityMap.insert(pair<char, priorityOperator>('-', sub));
        priorityMap.insert(pair<char, priorityOperator>('*', mul));
        priorityMap.insert(pair<char, priorityOperator>('/', divide));
        priorityMap.insert(pair<char, priorityOperator>('(', openBracket));
    }

    /**
     * The function return if the string is binary expression.
     * @param strExpression - string&.
     * @return bool.
     */
    bool IsBinaryOperator(string &strExpression);


    /**
     * The function return new binary Expression according to insert string.
     * @param oper - string&.
     * @param exp1 - Expression*.
     * @param exp2 - Expression*.
     * @return Expression*.
     */
    Expression *createBinabryExpression(string &oper, Expression *exp1, Expression *exp2);

    /**
     * The function return if the string that insert is number.
     * @param strExpression - string&.
     * @return bool.
     */
    bool IsNumber(string &strExpression);


    /**
     * The function gets deque with strings of expressions
     * in postfix oprder and return Expression in accordance.
     *
     * @param strExpressions - deque<string>.
     * @return Expression*.
     */
    Expression* postfixCalculator(deque<string> strExpressions);


    /**
     * The function gets a string and return
     * deque with string acoording to ShuntionYard algorithm.
     *
     * @param str - string of expression.
     * @return deque<string>.
     */
    deque<string> shuntingYardAlgorithm(string str);

public:
    /**
     * The function gets a string of expression and return Expression in accordance.
     * @param strExpress - string&.
     * @return Expression*.
     */
    Expression* expressionFromString(string& strExpress) {
        return postfixCalculator(shuntingYardAlgorithm(strExpress));
    }
};