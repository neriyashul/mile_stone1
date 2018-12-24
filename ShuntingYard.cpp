
#include "ShuntingYard.h"

/**
     * The function return if the string is binary expression.
     * @param strExpression - string&.
     * @return bool.
     */
bool ShuntingYard::IsBinaryOperator(string &strExpression) {
    {
        if (strExpression.size() != 1) {
            return false;
        }

        switch (strExpression.at(0)) {
            case '+':
            case '-':
            case '*':
            case '/':
                return true;
            default:
                return false;
        }
    }
}


/**
     * The function return new binary Expression according to insert string.
     * @param oper - string&.
     * @param exp1 - Expression*.
     * @param exp2 - Expression*.
     * @return Expression*.
     */
Expression* ShuntingYard::createBinabryExpression(string &oper,
                            Expression *exp1, Expression *exp2) {
    // the function IsBinaryOperator checked that the size of 'oper' is 1.
    switch (oper.at(0)) {
        case '+':
            return new AddExp(exp1, exp2);
        case '-':
            return new MinusExp(exp1, exp2);
        case '*':
            return new MulExp(exp1, exp2);
        case '/':
            return new DivExp(exp1, exp2);
        default:
            return nullptr;
    }
}


/**
     * The function return if the string that insert is number.
     * @param strExpression - string&.
     * @return bool.
     */
bool ShuntingYard::IsNumber(string &strExpression) {
    unsigned long i = 0;
    if (strExpression.empty())
        return false;
    else if (strExpression[0] == '-') {
        ++i;
    }
    for (; i < strExpression.size(); ++i) {
        if ((strExpression[i] != '.')
            && (strExpression[i] < '0' || strExpression[i] > '9'))
            return false;
    }
    return true;
}


/**
     * The function gets deque with strings of expressions
     * in postfix oprder and return Expression in accordance.
     *
     * @param strExpressions - deque<string>.
     * @return Expression*.
     */
Expression* ShuntingYard::postfixCalculator(deque<string> strExpressions)  {
    //int EvaluatePostfix(string expression)
    {
        stack<Expression *> numbers;

        for (auto &strExpression : strExpressions) {

            // If character is operator, pop two elements from stack, perform operation and push the result back.
            if (IsBinaryOperator(strExpression)) {
                // Pop two operands.
                Expression *operand2 = numbers.top();
                numbers.pop();
                Expression *operand1 = numbers.top();
                numbers.pop();
                // Perform operation
                Expression *result = createBinabryExpression(strExpression, operand1, operand2);
                if (result == nullptr) {
                    throw "there is a problem with create binary expression";
                }
                //Push back result of operation on stack.
                numbers.push(result);
            } else if (IsNumber(strExpression)) {
                numbers.push(new Num(strExpression));
            }
        }

        // If expression is in correct format, the Stack will finally have one element. This will be the output.
        if (numbers.size() != 1) {
            throw "problem with the expression format";
        }
        return numbers.top();
    }
}


/**
     * The function gets a string and return
     * deque with string acoording to ShuntionYard algorithm.
     *
     * @param str - string of expression.
     * @return deque<string>.
     */
deque<string> ShuntingYard::shuntingYardAlgorithm(string str) {
    map<char, priorityOperator> priorityMap;
    addPriorityOperator(priorityMap);

    deque<string> myQueue;
    stack<char> myStack;

    string num;
    bool isLastCharWasNum = false;

    for (char currentChar : str) {
        if (currentChar == ' ') {
            continue;
        }
        // if current char is number or '.':
        if ((currentChar <= '9' && currentChar >= '0')
            || currentChar == '.') {
            isLastCharWasNum = true;
            num += currentChar;
            continue;

        } else if (!num.empty()) { // if the previous chars was number and now isn't.
            myQueue.push_back(num);
            num = "";
        }


        // if the next num is negative:
        if (currentChar == '-' && !isLastCharWasNum) {
            num += "-";
            isLastCharWasNum = false;
            continue;
        }

        isLastCharWasNum = false;

        switch (currentChar) {
            case '(':
                myStack.push(currentChar);
                continue;
            case ')':
                while (myStack.top() != '(') {
                    myQueue.emplace_back(1, myStack.top());
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

    if (!num.empty()) { // if the last token that read was number:
        myQueue.push_back(num);
    }

    // add all the stack's argument to the queue.
    while (!myStack.empty()) {
        myQueue.emplace_back(1, myStack.top());
        myStack.pop();
    }

    return myQueue;
}