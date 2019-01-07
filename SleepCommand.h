//
// Created by neriya on 12/25/18.
//

#ifndef MILE_STONE1_SLEEPCOMMAND_H
#define MILE_STONE1_SLEEPCOMMAND_H


#include "Command.h"
#include "ExpressionFactory.h"
#include <thread>

class SleepCommand : public Command {
    ExpressionFactory* ef;
public:
    explicit SleepCommand(ExpressionFactory* expressFactor) {
        ef = expressFactor;
    }
    void doCommand(std::vector<std::string> &v) override;
};


#endif //MILE_STONE1_SLEEPCOMMAND_H
