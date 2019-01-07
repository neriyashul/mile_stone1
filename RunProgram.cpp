#include "RunProgram.h"
using namespace std;

RunProgram::~RunProgram() {
    parser.end();


    for (pair<string, Var*> p : variable) {
            delete(p.second);
    }

    for(Expression* e:this->expressions) {
        delete(e);
    }

    for(pair<int, double*> d: valuesOfPaths) {
        delete (d.second);
    }
}


void RunProgram::addVectorExpression(vector<Expression*>& ve) {
    expressions.insert(
            expressions.end(),
            make_move_iterator(ve.begin()),
            make_move_iterator(ve.end()));
}

void RunProgram::run(string &input) {
    vector<string> vs = lexer.lexer(input);
    vector<Expression*>ve = parser.parse(vs);
    for (Expression* e: ve) {
        e->calculate();
    }
    addVectorExpression(ve);
}

bool RunProgram::isContinue(string &line)  {
    string firstWord = line.substr(0,line.find(' '));
    return parser.isConditionCommand(firstWord);
}