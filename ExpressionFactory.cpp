
#include "ExpressionFactory.h"

using namespace std;

void ExpressionFactory::addPriorityOperator(map<char, ExpressionFactory::priorityOperator> &priorityMap)  {
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
bool ExpressionFactory::isBinaryOperator(unsigned sizeOfStack, string& str) {
    {
        if (str.size() != 1) {
            return false;
        }

        string strOpertor = STR_OF_BINARY_OPERATOR;

        if (str[0] == '-') {
            // if '-' is because the num before is negative -> return false.
            return (sizeOfStack > 1);
        } else {
            // check if str is is one of the operator.
            return  (strOpertor.find_first_of(str) != string::npos);
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
Expression* ExpressionFactory::createBinabryExpression(string &oper,
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
bool ExpressionFactory::isDoubleNumber(const string &str) {
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
Expression* ExpressionFactory::postfixCalculator(deque<string> strExpressions)  {
    //int EvaluatePostfix(string expression)

    // check if there is minus which not operation.
    bool isPrevMinus = false;
    stack<Expression *> numbers;

    for (string& str : strExpressions) {
        // If character is operator, pop two elements from stack, perform operation and push the result back.
        if (isBinaryOperator(static_cast<unsigned int>(numbers.size()), str)) {
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
                numbers.push(new MinusExp(new Num(0), new Num(str)));
                isPrevMinus = false;
            } else {
                numbers.push(new Num(str));
            }
        } else if (isVar(str)) {
            Var* e = new Var;
            // copy by value the parameter from (*variables)[str] to e.
            e->setExpression(new Num((*variables)[str]->calculate()));
            string s = (*variables)[str]->getPath();
            e->setPath(s);


            if (isPrevMinus) {
                numbers.push(new MinusExp(new Num(0), e));
                isPrevMinus = false;
            } else {
                numbers.push(e);
            }
        } else if (str == "-") {
            isPrevMinus = true;
        }
    }

    // If expression is in correct format, the Stack will finally have one element.
    // This will be the output.
    if (numbers.size() != 1) {
        throw "problem with the expression format";
    }
    return numbers.top();
}

/**
 * the function return if the insert char is condition operator.
 * @param c - char
 * @return bool.
 */
bool ExpressionFactory::isConditionOperator (string& s) {
    switch (s[0]) {
        case '=':
        case '<':
        case '>':
        case '!':
            return true;
        default:
            return false;
    }
}


vector<vector<string>>
          ExpressionFactory::divideToExpressions(
                   vector<string> &argument)  {

    vector<vector<string>> expressions;
    vector<string> currentExpression;

    string binaryOperator = STR_OF_BINARY_OPERATOR;
    size_t right;
    size_t left;
    bool openBarcket;
    bool closeBarcket;
    long size = argument.size();

    for (int i = 0; i < size - 1; ++i) {

        // if argument[i] is condition operatir -> its the end.
        if (isConditionOperator(argument[i])) {
            if (!currentExpression.empty()) {
                expressions.push_back(currentExpression);
                currentExpression.clear();
            }
            continue;
        }

        currentExpression.push_back(argument[i]);

        // find_first_of any binary operator.
        right = binaryOperator.find_first_of(argument[i]);
        left = binaryOperator.find_first_of(argument[i+1]);
        openBarcket = (argument[i] == "(");
        closeBarcket = (argument[i+1] == ")");

        /* argument[i] is the end of current expression
         * if none of the following is occur:
         *      a) there is binary operator in argument[i].
         *      b) there is binary operator in argument[i+1].
         *      c) there is openBarcket in argument[i]
         *      d) there is closeBarcket in argument[i+1]
         */
        if (right == string::npos && !openBarcket
            && left == string::npos && !closeBarcket) {
            expressions.push_back(currentExpression);
            currentExpression.clear();
        } else {
            continue;
        }
    }
    if (argument[size - 1] != "{") {
        // add the last argument to currentExpression.
        currentExpression.push_back(argument[size - 1]);
        expressions.push_back(currentExpression);
    }
    return expressions;
}