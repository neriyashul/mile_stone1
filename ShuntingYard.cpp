
#include "ShuntingYard.h"
#include "Num.h"

/**
     * The function return if the string is binary expression.
     * @param strExpression - string&.
     * @return bool.
     */
bool ShuntingYard::isBinaryOperator(unsigned index, string& str, string& prev) {
    {
        if (str.size() != 1) {
            return false;
        }

        switch (str[0]) {
            case '-':
                if (index < 1 || (!(isDoubleNumber(prev))
                                        && !isVar(prev)) {
                    return false;
                }
            case '+':
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
     * The function return if the string that insert is float/ double number.
     * @param strExpression - string&.
     * @return bool.
     */
bool ShuntingYard::isDoubleNumber(const string &str) {
    if (str.empty()) {
        return false;
    }

    bool sawDot = false;
    for (char c : str) {
        // if c isn't digit nor first dot:
        if (! (isdigit(c) || (c == '.' && !sawDot))) {
            return false;
        }
        sawDot = sawDot || (c == '.');
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

        // check if there is minus which not operation.
        bool isPrevMinus = false;
        stack<Expression *> numbers;
        unsigned index = 0;
        for (string& str : strExpressions) {
            // If character is operator, pop two elements from stack, perform operation and push the result back.
            if (isBinaryOperator(index, str, strExpressions[index - 1])) {
                // Pop two operands.
                Expression *operand2 = numbers.top();
                numbers.pop();
                Expression *operand1 = numbers.top();
                numbers.pop();
                // Perform operation
                Expression *result = createBinabryExpression(str, operand1, operand2);
                if (result == nullptr) {
                    throw "there is a problem with create binary expression";
                }
                //Push back result of operation on stack.
                numbers.push(result);
            } else if (isDoubleNumber(str)) {
                if (isPrevMinus) {
                    numbers.push(new MinusExp(new Num(0), (*variables)[str]));
                    isPrevMinus = false;
                } else {
                    numbers.push(new Num(str));
                }
            } else if (isVar(str)) {
                if (isPrevMinus) {
                    numbers.push(new MinusExp(new Num(0), (*variables)[str]));
                    isPrevMinus = false;
                } else {
                    numbers.push((*variables)[str]);
                }
            } else if (str == "-") {
                isPrevMinus = true;
            }

            ++index;
        }

        // If expression is in correct format, the Stack will finally have one element.
        // This will be the output.
        if (numbers.size() != 1) {
            throw "problem with the expression format";
        }
        return numbers.top();

}



/**
     * The function gets a string and return
     * deque with string acoording to ShuntionYard algorithm.
     *
     * @param str - string of expression.
     * @return deque<string>.
     */
deque<string> ShuntingYard::shuntingYardAlgorithm(vector<string>& vecStr) {
    map<char, priorityOperator> priorityMap;
    addPriorityOperator(priorityMap);

    deque<string> myQueue;
    stack<char> myStack;

    bool isPrevWasNumOrVar = false;

    for (string& currentstr : vecStr) {
        if (currentstr.empty() || currentstr == " ") {
            continue;
        }
        // currentStr is var or number:
        if (isDoubleNumber(currentstr) || isVar(currentstr)) {
            isPrevWasNumOrVar = true;
            myQueue.push_back(currentstr);
            continue;
        }

        // if the next num that will be next is negative:
        if (currentstr == "-" && !isPrevWasNumOrVar) {
            myQueue.push_back(currentstr);
            continue;
        }

        isPrevWasNumOrVar = false;

        if (currentstr.size() == 1) {
            char currentChar = currentstr[0];
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
        } else {
            throw "unrecognie string";
        }
    }

    // add all the stack's argument to the queue.
    while (!myStack.empty()) {
        myQueue.emplace_back(1, myStack.top());
        myStack.pop();
    }

    return myQueue;
}