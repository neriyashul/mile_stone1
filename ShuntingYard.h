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


    void addPriorityOperator(map<char, priorityOperator> &priorityMap) {
        priorityMap.insert(pair<char, priorityOperator>('+', add));
        priorityMap.insert(pair<char, priorityOperator>('-', sub));
        priorityMap.insert(pair<char, priorityOperator>('*', mul));
        priorityMap.insert(pair<char, priorityOperator>('/', divide));
        priorityMap.insert(pair<char, priorityOperator>('(', openBracket));
    }

    bool IsBinaryOperator(string &strExpression);


    Expression *createBinabryExpression(string &oper, Expression *exp1, Expression *exp2);

    bool IsNumber(string &strExpression);


    Expression *postfixCalculator(deque<string> strExpressions);


    deque<string> shuntingYardAlgorithm(string str);

public:
    Expression* expressionFromString(string& strExpress) {
        return postfixCalculator(shuntingYardAlgorithm(strExpress));
    }
};