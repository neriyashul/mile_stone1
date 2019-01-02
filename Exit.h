//
// Created by neriya on 12/27/18.
//

#ifndef MILE_STONE1_EXIT_H
#define MILE_STONE1_EXIT_H


#include "Command.h"

class Exit : public Command {
public:
    virtual void doCommand(std::vector<std::string>& v) {
        exit(1);
    }
};


#endif //MILE_STONE1_EXIT_H
