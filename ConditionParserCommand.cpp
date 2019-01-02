#include "ConditionParserCommand.h"


/**
 * the function return the condition in the string
 *
 * @param v - const vector<string>&
 * @return vector<string>
 */
vector<string> conditionInString(const vector<string>& v) {
    vector<string> cond;
    for (const string& str: v) {
        if (strcmp(str.c_str(), STR_END_OF_CONDITION) != 0) {
            cond.push_back(str);
        }
    }
    return cond;
}


/**
 * the function return if the insert char is condition operator.
 * @param c - char
 * @return bool.
 */
bool isConditionOperator (char c) {
    switch (c) {
        case '=':
        case '<':
        case '>':
        case '!':
            return true;
        default:
            return false;
    }
}

/**
 *
 * the function get vector of string
 * and return the all string as a long one.
 * @param strs - vector<string>&.
 * @return string.
 */
string ConditionParserCommand::combineStrings(const vector<string>& strs) {
    string str;
    for (const string& s: strs) {
        str += s;
    }
    return str;
}


/**
 * the function return the condition divided to 3.
 * 1) left operand
 * 2) operator
 * 3) right operand
 * @param v - vector<string>
 * @return vector<vector<string>>.
 */
vector<vector<string>> ConditionParserCommand
            ::createConditionVec(const vector<string>& v) {

    vector<string> operatorStr;
    vector<string> condStr =  conditionInString(v);

    unsigned long size = condStr.size();

    for (unsigned i = 0; i < size; ++i) {
        if (isConditionOperator(condStr[i].at(0))) {
            vector<string> leftOper(i - 1);
            vector<string> rightOper(size - i);
            operatorStr.push_back(condStr[i]);
            copy(condStr.begin(), condStr.begin() + condStr[i].size() - 1, leftOper.begin());
            // enter the strings into vector
            vector<vector<string>> ret;
            ret.push_back(leftOper);
            ret.push_back(operatorStr);
            ret.push_back(rightOper);
            return ret;
        }
    }
    // enter the strings into vector
    vector<vector<string>> ret;
    // create an empty vector for the right operand.
    vector<string> r;
    // the left operand is the inserted v.
    ret.push_back(v);
    ret.push_back(operatorStr);
    ret.push_back(r);
    return ret;
}

/**
 * the function handle with the condition.
 * the func gets vector of string and return vector of string
 * @param v
 * @return
 */
vector<string> ConditionParserCommand
           ::conditionHandle(const vector<string>& v) {

    vector<vector<string>> conditionVec = createConditionVec(v);
    addToScope(v);
    string left = combineStrings(conditionVec[0]);
    string oper = combineStrings(conditionVec[1]);
    string right = combineStrings(conditionVec[2]);
    vector<string> strVector;
    strVector.push_back(left);
    strVector.push_back(oper);
    strVector.push_back(right);
    return strVector;
}


/**
 * The function gets 2 Expressions and condition.
 *           and return if the condition satisfy.
 *
 * The condition are:
 * 1) !=
 * 2) ==
 * 3) <=
 * 4) >=
 * 5) <
 * 6) >
 * 7) !
 * 8) none (no condition) - return exp1->calculate
 *
 * @param condition - const char*
 * @param exp1 - Expression.
 * @param exp2 - Expression.
 * @return bool.
 */
bool ConditionParserCommand::isConditionSatisfy(
        const string& condition, Expression* exp1, Expression* exp2) {

    // if there is no condition - return exp1->calc.
    if (condition.empty()){
        return (bool) exp1->calculate();
    }
    // if there is 2 char in the condition:
    if (condition.size() > 1 && condition[1] == '=') {
        switch (condition[0]) {
            // case !=
            case '!':
                return (exp1->calculate() != exp2->calculate());
                // case <=
            case '<':
                return (exp1->calculate() <= exp2->calculate());
                // case ==
            case '=':
                return (exp1->calculate() == exp2->calculate());
                // case >=
            case '>':
                return (exp1->calculate() >= exp2->calculate());
            default:
                return false;
        }
    } else {
        switch(condition[0]) {
            case '<':
                return (exp1->calculate() < exp2->calculate());
            case'>':
                return (exp1->calculate() > exp2->calculate());
            case '!':
                return !(bool)exp1->calculate();
            default:
                return false;
        }
    }
}

void ConditionParserCommand::addToScope(const vector<string> &strVec) {
    unsigned numOfOpenerScope = 0;
    unsigned numOfCloserScope = 0;
    unsigned long startScope = 1;
    unsigned long endScope = 0;

    unsigned long i = 0;
    try {
        for (; numOfOpenerScope == numOfCloserScope; ++i) {
            if (strVec[i] == STR_START_OF_SCOPE) {
                if (numOfOpenerScope == 1) {
                    startScope = i;
                    continue;
                }
                ++numOfOpenerScope;
            } else if (strVec[i] == STR_END_OF_SCOPE) {
                ++numOfCloserScope;
            }
        }
        endScope = i;
    } catch (...) {
        throw out_of_range("the num of open and close scope not fit");
    }

    vector<string> dummy(endScope - startScope);
    inScope = dummy;
    copy(strVec.begin() + startScope,
            strVec.begin() + endScope, inScope.begin());
}