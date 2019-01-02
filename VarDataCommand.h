#ifndef MILE_STONE1_VARDATACOMMAND_H
#define MILE_STONE1_VARDATACOMMAND_H


#include <string>
#include <unordered_map>
#include <mutex>
#include "Threads.h"
#include "Command.h"
#include "Var.h"
#include "ShuntingYard.h"
#include "Num.h"
#include "bindVar.h"


class VarDataCommand : public Command {
    std::unordered_map<std::string, int>* numsOfPathsNames;
    std::unordered_map<int, double>* valuesOfPathsNums;
    std::unordered_map<std::string,Var*>* variables;
    std::mutex *mtxServer = nullptr;

public:
    VarDataCommand(std::unordered_map<std::string, int>* names,
                   std::unordered_map<int, double>* values,
                   std::unordered_map<std::string,Var*>* vars, std::mutex* m) {
        this->numsOfPathsNames = names;
        this->valuesOfPathsNums = values;
        variables = vars;
        this->mtxServer = m;
    }

    void addVarToMap(std::string& name, Var* v) {
        (*variables).insert(pair<string, Var*>(name, v));
    }

    Var* createVar(bool isBind, std::vector<std::string>& expression) {
        Var *var = new Var;

        // if expression is some path.
        if (*(expression.at(0).begin()) == '"' && *(expression.at(0).end()) == '"') {
            // removeApostrophes.
            expression.erase(expression.begin());
            expression.erase(expression.end());
            if (isBind) {
                var->setExpression(new bindVar(
                        &valuesOfPathsNums->at(numsOfPathsNames->at(expression[0]))));
            } else {
                var->setExpression(new Num(
                        valuesOfPathsNums->at(numsOfPathsNames->at(expression[0]))));
            }
        } else if (isBind) { // if expression is only var's name and is bind.
            // var.expression = var which return from variable.
            var->setExpression(variables->at(expression[0]));

        }else { // if expression is arithmetic including variables.
            ShuntingYard sy(variables);
            double d = sy.expressionFromString(expression)->calculate();
            var->setExpression(new Num(d));
        }

        return var;
    }


    void doCommand(std::vector<std::string>& v) override {
        // if there is problem with the arguments:
        if (v.size() < 3 || v[1] != "=" ||
            v[0].empty()|| v[v.size()-1].empty()) {
            throw "wrong numbers of arguments";
        }

        // lock mtxServer to make no changes in the maps.
        lock_guard<mutex> lock(*this->mtxServer);

        bool isBind = (v[2] == "bind");

        Var* var = createVar();
        addVarToMap(v[0],var);

    }
};


#endif //MILE_STONE1_VARDATACOMMAND_H
