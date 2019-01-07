#include "ShuntingYard.h"

using namespace std;

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



std::vector<Expression*> ShuntingYard::expressionFromString(vector<string> &arguments)  {
    vector<Expression*> expressions;
    if (arguments.empty()) {
        return expressions;
    }
    vector<vector<string>> strExpressions = divideToExpressions(arguments);

    for (vector<string> &expression: strExpressions) {
        if (!arguments.empty()) {
            expressions.push_back(postfixCalculator(
                    shuntingYardAlgorithm(expression)));
        }
    }
    return  expressions;

}
