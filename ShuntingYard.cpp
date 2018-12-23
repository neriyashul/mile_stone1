#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include "Expression.h"

#define END_NUMBER ","

using namespace std;

enum priorityOperator {
    openBracket, add, sub = add, mul, divide = mul
};


void addPriorityOperator(map<char, priorityOperator>& priorityMap) {
    priorityMap.insert(pair<char, priorityOperator>('+', add));
    priorityMap.insert(pair<char, priorityOperator>('-', sub));
    priorityMap.insert(pair<char, priorityOperator>('*', mul));
    priorityMap.insert(pair<char, priorityOperator>('/', divide));
    priorityMap.insert(pair<char, priorityOperator>('(', openBracket));
}

bool IsBinaryOperator(string& strExpression) {
    if (strExpression.size() != 1) {
        return false;
    }

    switch (strExpression.at(0))  {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}


Expression* createBinabryExpression(string& oper, Expression* exp1, Expression* exp2) {
    // the function IsBinaryOperator checked that the size of 'oper' is 1.
    switch (oper.at(0)) {
        case '+':
            return new AddExp(exp1, exp2);
        case '-':
            return new SubExp(exp1, exp2);
        case '*':
            return new MulExp(exp1, exp2);
        case '/':
            return new DivExp(exp1, exp2);
        default:
            return nullptr;
    }
}



Expression* postfixCalculator(deque<string> strExpressions) {
    //int EvaluatePostfix(string expression)
    {
        stack<Expression*> numbers;

        for(int i = 0; i< strExpressions.size(); ++i) {

                // If character is operator, pop two elements from stack, perform operation and push the result back.
            if(IsBinaryOperator(strExpressions[i])) {
                // Pop two operands.
                Expression* operand2 = numbers.top();
                numbers.pop();
                Expression* operand1 = numbers.top();
                numbers.pop();
                // Perform operation
                Expression* result = createBinabryExpression(strExpressions[i], operand1, operand2);
                if (result == nullptr) {
                    throw "there is a problem with create binary expression";
                }
                //Push back result of operation on stack.
                numbers.push(result);
            } else if(IsNumericDigit(strExpressions[i])){
                numbers.push(new Num(strExpressions[i]));
            }
        }

        // If expression is in correct format, the Stack will finally have one element. This will be the output.
        if (numbers.size() != 1) {
            throw "problem with the expression format";
        }
        return numbers.top();
    }
}



deque<string> shuntingYard(string str) {
    map<char, priorityOperator> priorityMap;
    addPriorityOperator(priorityMap);

    deque <string> myQueue;
    stack <char>  myStack;

    string num;
    bool isLastCharWasNum = false;
    bool isNumIsNeg = false;

    for (char currentChar : str) {
        if (currentChar == ' ') {
            continue;           }
        if (currentChar <= '9' && currentChar >= '0') {
            isLastCharWasNum = true;
            num += currentChar;
            continue;

        } else if (!num.empty()) { // if the previous chars was number and now isn't.
            if (isNumIsNeg) {
                num = "-" + num; }
            myQueue.push_back(num);
            myQueue.emplace_back(END_NUMBER);
            num = "";
            isNumIsNeg = false;
        }

        if(currentChar == '-' && !isLastCharWasNum) {
            isNumIsNeg = true;
        }
        isLastCharWasNum = false;

        switch (currentChar) {
            case '(':
                myStack.push(currentChar);
                continue;
            case ')':
                while (myStack.top() != '(') {
                    myQueue.emplace_back(1,myStack.top());
                    myStack.pop();
                }
                myStack.pop();
                continue;
            default:

                // if operator: +,-,*,/ and there is operator with greater priority in the stack.
                while (!myStack.empty() && (priorityMap.at(myStack.top())) > (priorityMap.at(currentChar))) {
                    // move the first argument in the stack to the queue.
                    myQueue.emplace_back(1, myStack.top());
                    myStack.pop();
                }
                // add currentChar to stack
                myStack.push(currentChar);
                continue;
        }
    }

    if (!num.empty()){ // if the last token that read was number:
        myQueue.push_back(num);
    }

    // add all the stack's argument to the queue.
    while (!myStack.empty()) {
        myQueue.emplace_back(1,myStack.top());
        myStack.pop();
    }

    return myQueue;
}

