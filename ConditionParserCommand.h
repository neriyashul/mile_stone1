#ifndef MILE_STONE1_CONDITIONPARSERCOMMAND_H
#define MILE_STONE1_CONDITIONPARSERCOMMAND_H

#include "Command.h"
#include <vector>
#include "Expression.h"
#include "ShuntingYard.h"

#define STR_END_OF_CONDITION "{"

class Parser;

class ConditionParserCommand : public Command {
protected:
    vector<string> inSegment; // everything that after the condition.
public:

    /**
 * The function gets 2 Expressions and condition.
 *         and return if the condition is satisfy.
 *
 * The condition are:
 * 1) !=
 * 2) ==
 * 3) <=
 * 4) >=
 * 5) <
 * 6) >
 * 7) !
 * 8) none
 *
 * @param condition - const char*
 * @param exp1 - Expression.
 * @param exp2 - Expression.
 * @return bool.
 */
 bool isConditionSatisfy(const char* condition, Expression* exp1, Expression* exp2);

 /**
  * the function parse all the things inside the condition.
  */
 void callToParser() {
     Parser p;
     p.parse(inSegment);
 }


 /**
  * the function combine all the string into one.
  * @param strs
  * @return
  */
    string combineStrings(vector<string> strs);

 /**
  * The function gets a vector with string and return vector with:
  * 1) left size of the operator in the condition.
  * 2) operator
  * 3) right size of the operator in the condition.
  * @param v - const vector<string>& v.
  * @return vector<string>&.
  */
 vector<vector<string>> createConditionVec(const vector<string>& v);



 Expression* expFromShuntingYard(string& str) {
     ShuntingYard s;
     return s.expressionFromString(str);
    };



 /**
  * @overrite doCommand.
  */
 virtual void doCommand(vector<string>&) = 0;

    /**
    * The function insert string to inSegmaent.
    * @param str.
    */
 void AddStringInSegment(string& str) {
     inSegment.push_back(str);
 }

};


#endif //MILE_STONE1_CONDITIONPARSER_H
