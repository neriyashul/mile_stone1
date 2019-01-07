
#ifndef MILE_STONE1_PRINTCOMMAND_H
#define MILE_STONE1_PRINTCOMMAND_H


#include <iostream>
#include "Command.h"
#include "Var.h"
#include "ExpressionFactory.h"

class PrintCommand : public Command {
    bool isString = false;
    std::unordered_map<std::string,Var*>* variables;
    ExpressionFactory* expressFactor = nullptr;
public:
    PrintCommand(ExpressionFactory* ef, std::unordered_map<std::string,Var*>* vars) {
        variables = vars;
        expressFactor = ef;
    }

    void doCommand(std::vector<std::string>& v) override;

};


#endif //MILE_STONE1_PRINT_H
