//
// Created by neriya on 1/2/19.
//

#ifndef MILE_STONE1_EQUALIZE_H
#define MILE_STONE1_EQUALIZE_H


#include <unordered_map>
#include "Command.h"
#include "Var.h"

class Equalize : Command {
    std::unordered_map<int, double>* valuesOfPathsNums;
    std::unordered_map<std::string, int>* numsOfPathsNames;
    std::unordered_map<std::string,Var*>* variables;

    Equalize(std::unordered_map<std::string, Var*> *vars,
             std::unordered_map<int, double>* values,
             std::unordered_map<std::string, int>* names) {
        // init maps
        this->variables = vars;
        this->valuesOfPathsNums = values;
        this->numsOfPathsNames = names;
    }

    void doCommand(std::vector<std::string> &args) override {
        if (args.size() < 2) {
            throw "wrong numbers of arguments";
        }

        Var* left = variables->at(args[0]);
        //valuesOfPathsNums->at(numsOfPathsNames->at(args[0]));

        int curArg = 1;
        while (curArg < args.size()) {
            this->right.push_back(code[index]);
            ++index;
        }
    }
};


#endif //MILE_STONE1_COMPARE_H
