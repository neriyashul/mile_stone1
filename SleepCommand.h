//
// Created by neriya on 12/25/18.
//

#ifndef MILE_STONE1_SLEEPCOMMAND_H
#define MILE_STONE1_SLEEPCOMMAND_H


#include "Command.h"
#include "ShuntingYard.h"
#include <thread>

class SleepCommand : public Command {
    ShuntingYard* sy;
public:
    explicit SleepCommand(ShuntingYard* shunY) {
        sy = shunY;
    }
    void doCommand(std::vector<std::string> &v) override;
};


#endif //MILE_STONE1_SLEEPCOMMAND_H
