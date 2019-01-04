//
// Created by neriya on 1/2/19.
//

#ifndef MILE_STONE1_PRINTCOMMAND_H
#define MILE_STONE1_PRINTCOMMAND_H


#include <iostream>
#include "Command.h"
#include "Var.h"
#include "ShuntingYard.h"

class PrintCommand : public Command {
    std::unordered_map<std::string,Var*>* variables;
    ShuntingYard* sy = nullptr;
public:
    PrintCommand(ShuntingYard* shuntY, std::unordered_map<std::string,Var*>* vars) {
        variables = vars;
        sy = shuntY;
    }

    void doCommand(std::vector<std::string>& v) override;

};


#endif //MILE_STONE1_PRINT_H
