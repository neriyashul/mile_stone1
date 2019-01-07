//
// Created by neriya on 1/2/19.
//

#ifndef MILE_STONE1_EQUALIZE_H
#define MILE_STONE1_EQUALIZE_H


#include <unordered_map>
#include <mutex>
#include "Command.h"
#include "Var.h"
#include "ExpressionFactory.h"

class Equalize : public Command {

    bool* isNewMassage = nullptr;
    ExpressionFactory* expressFactor;
    std::unordered_map<int, double*>* valuesOfPaths = nullptr;
    std::unordered_map<std::string, int>* numsOfPathsNames = nullptr;
    std::unordered_map<std::string,Var*>* variables = nullptr;
    std::string* massage = nullptr;
    std::mutex* clientMtx = nullptr;
    Var* name = nullptr;
public:
    Equalize(std::unordered_map<std::string, Var*> *vars,
                  ExpressionFactory* ef, bool* isNewMass,
                    std::string* massag, std::mutex* mtx);

    void doCommand(std::vector<std::string> &args) override;
};


#endif //MILE_STONE1_COMPARE_H
