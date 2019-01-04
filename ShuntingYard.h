
#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include "Expression.h"
#include "MathExpressions.h"
#include "Var.h"
#include "Num.h"


using namespace std;


class ShuntingYard {
    std::unordered_map<std::string,Var*>* variables;

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
     * the function return if the enter string is a name of variable.
     * @param name - string&.
     * @return bool.
     */
    bool isVar(string& name) {
        return (variables->count(name) > 0);
    }

    /**
     * The function return if the string is binary expression.
     *
     */
    bool isBinaryOperator(unsigned, string&);


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
    bool isDoubleNumber(const string &);


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
     * @param vecStr - vector<string> of expression.
     * @return deque<string>.
     */
    deque<string> shuntingYardAlgorithm(vector<string>& vecStr);

public:
    explicit ShuntingYard(std::unordered_map<std::string,Var*>* vars) {
        variables = vars;
    }
    /**
     * The function gets a string of expression and return Expression in accordance.
     * @param strExpress - string&.
     * @return Expression*.
     */
    Expression* expressionFromString(vector<string>& expression);
};


#endif // SHUNTINGYARD_H