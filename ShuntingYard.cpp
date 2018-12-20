#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>

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


deque<string> shuntingYard(string str) {
    map<char, priorityOperator> priorityMap;
    addPriorityOperator(priorityMap);

    deque <string> myQueue;
    stack <char>  myStack;

    string num;

    for (char currentChar : str) {
        // if the previous chars was numbers and now isn't.
        if (!num.empty() && (currentChar > '9' || currentChar < '0')){
            myQueue.push_back(num);
            num = "";
        }

        switch (currentChar) {
            case ' ':
                continue;
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
                // if number
                if (currentChar <= '9' && currentChar >= '0') {
                    num += currentChar;
                    continue;
                }

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
    // if the last token that read was number:
    if (!num.empty()){
        myQueue.push_back(num);
    }

    // add all the stack's argument to the queue.
    while (!myStack.empty()) {
        myQueue.emplace_back(1,myStack.top());
        myStack.pop();
    }

    return myQueue;
}

