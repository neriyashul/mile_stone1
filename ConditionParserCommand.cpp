#include "ConditionParserCommand.h"
#include "string.h"


/**
 * the func return as string the all condition
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


bool isIfOperator (char c) {
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

string ConditionParserCommand::combineStrings(vector<string> strs) {
    string str;
    for (string& s: strs) {
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
vector<vector<string>> ConditionParserCommand::createConditionVec(const vector<string>& v) {
    vector<string> operatorStr;
    vector<string> condStr =  conditionInString(v);
    size_t pos = 0;
    unsigned long size = condStr.size();
    for (unsigned i = 0; i < size; ++i) {
        if (isIfOperator(condStr[i].at(0))) {
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
    vector<string> r;
    ret.push_back(v);
    ret.push_back(operatorStr);
    ret.push_back(r);
    return ret;
}


vector<string> ConditionParserCommand::conditionHandle(const vector<string>& v) {
    vector<vector<string>> condVec = createConditionVec(v);
    addToSegment(v);
    string left = combineStrings(condVec[0]);
    string oper = combineStrings(condVec[1]);
    string right = combineStrings(condVec[2]);
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
        const char* condition, Expression* exp1, Expression* exp2) {

    // if there is no condition - return exp1->calc.
    if (!strcmp(condition, "")){
        return (bool) exp1->calculate();
    }
    // if there is 2 char in the condition:
    if (condition[1] == '=') {
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

void ConditionParserCommand::addToSegment(vector<string> &strVec) {
    unsigned i = 0;
    for ( ; i < strVec.size(); ++i) {
        if (!strcmp(strVec[i].c_str(), STR_END_OF_LINE)) {
            break;
        }
    }
    vector<string> dummy(strVec.size() - i);
    inSegment = dummy;
    copy(strVec.begin() + i, strVec.end(), inSegment.begin());
}
