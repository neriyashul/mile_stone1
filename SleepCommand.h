//
// Created by neriya on 12/25/18.
//

#ifndef MILE_STONE1_SLEEPCOMMAND_H
#define MILE_STONE1_SLEEPCOMMAND_H


#include <unistd.h>
#include "Command.h"

class SleepCommand : public Command {
public:
    virtual void doCommand(std::vector<std::string> &v) {
        if (v.size()!= 1) {
            throw "wrong numbers of arguments";
        }
        std::string::size_type s;
        auto num = (unsigned ) std::stod(v[0], & s);
        if (s < v[0].size()) {
            throw "argument is not number";
        }

        sleep (num);
    }
};


#endif //MILE_STONE1_SLEEPCOMMAND_H
