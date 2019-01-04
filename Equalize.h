//
// Created by neriya on 1/2/19.
//

#ifndef MILE_STONE1_EQUALIZE_H
#define MILE_STONE1_EQUALIZE_H


#include <unordered_map>
#include <mutex>
#include "Command.h"
#include "Var.h"
#include "ShuntingYard.h"

class Equalize : public Command {

    bool* isNewMassage = nullptr;
    ShuntingYard* shunYard;
    std::unordered_map<int, double>* valuesOfPathsNums = nullptr;
    std::unordered_map<std::string, int>* numsOfPathsNames = nullptr;
    std::unordered_map<std::string,Var*>* variables = nullptr;
    string* massage = nullptr;
    mutex* clientMtx = nullptr;
public:
    Equalize(std::unordered_map<std::string, Var*> *vars,ShuntingYard& sy, bool* isNewMass, string* massag, mutex* mtx) {
        // init maps
        this->variables = vars;
        this->isNewMassage = isNewMass;
        this->massage = massag;
        shunYard = &sy;
        clientMtx = mtx;

        /*std::unordered_map<int, double>* values,
        std::unordered_map<std::string, int>* names,
        this->valuesOfPathsNums = values;
        this->numsOfPathsNames = names;*/
    }

    void doCommand(std::vector<std::string> &args) override {
        if (args.size() < 2) {
            throw "wrong numbers of arguments";
        }
        // lock mutex.
        lock_guard<mutex> lock(*clientMtx);

        Var* left = variables->at(args[0]);
        // delete the left var from the vector.
        args.erase(args.begin());
        double right = shunYard->expressionFromString(args)->calculate();
        *this->massage = "set " + *left->getPath() +  " " + to_string(right);
        //string a = *this->massage;
        *this->isNewMassage = true;
    }
};


#endif //MILE_STONE1_COMPARE_H
