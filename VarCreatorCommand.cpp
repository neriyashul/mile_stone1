
#include "VarCreatorCommand.h"

using namespace std;
VarDataCommand::VarDataCommand(unordered_map<string, int> *names,
                               unordered_map<int, double*> *values,
                               unordered_map<string, Var *> *vars, mutex *m,
                               ExpressionFactory *expressionFactory)  {
    this->numsOfPathsNames = names;
    this->valuesOfPaths = values;
    variables = vars;
    this->mtxServer = m;
    this->expressFactor = expressionFactory;
}

void removeApostrophes(string& str) {
    str.erase(str.begin());
    str.erase(str.end() - 1);
}


Var* VarDataCommand::createPathVar(bool isBind, string &path)  {
    removeApostrophes(path);
    Var* var = new Var();
    if (isBind) {
        // if path in the maps -> create bindVar, else -> create new Var.
        try {
            int numInMap = numsOfPathsNames->at(path);
            double* valuePath = valuesOfPaths->at(numInMap);
            var->setExpression(new BindVar(valuePath));
        } catch(...) { // if there is no such path:
            var->setExpression(new UntieVar(0));
        }
    } else {
        // find the path in the map:
        int numOfPath = numsOfPathsNames->at(path);
        var->setExpression(new Num (*(*valuesOfPaths)[numOfPath]));
    }
    var->setPath(path);
    return var;
}

Var* VarDataCommand::createBindVarByVarName(string& name) {
    Var* var = new Var;
    // var.expression = var which return from variable.
    Var* other = variables->at(name);
    var->setExpression(new BindVar(
            other->getExpression()->getIndexOfValue()));
    var->setPath(other->getPath());
    return var;
}

Var* VarDataCommand::createArithmeticOrUntieVar(vector<string> &expression) {
    Var* var = new Var;
    Expression* e = expressFactor->expressionFromString(expression).front();
    double d = e->calculate();
    var->setExpression(new Num(d));
    delete(e);
    return var;
}

Var* VarDataCommand::createVar(bool isBind, vector<string> &expression)  {
    // lock mtxServer to make no changes in the maps.
    lock_guard<mutex> lock(*this->mtxServer);

    // if expression's target is some path.
    if (*(expression.at(0).begin()) == '"' && *(expression.at(0).end() - 1) == '"') {
        return createPathVar(isBind, expression[0]);

    } else if (isBind) { // if expression is only var's name and is bind.
        return createBindVarByVarName(expression[0]);

    } else {

        // if expression is arithmetic including variables.
        return createArithmeticOrUntieVar(expression);

    }
}

void VarDataCommand::doCommand(vector<string> &v) {
    // if there is problem with the arguments:
    if (v.size() < 3 || v[1] != "=" ||
        v[0].empty()|| v[v.size()-1].empty()) {
        throw "wrong numbers of arguments";
    }

    bool isBind = (v[2] ==  "bind");
    if (isBind) {
        // delete bind
        v.erase(v.begin() + 2);
    }

    string name = v[0];
    // delete name and sign '='.
    v.erase(v.begin());
    v.erase(v.begin());

    Var* var = createVar(isBind, v);
    addVarToMap(name,var);
}

