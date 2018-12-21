#ifndef MILE_STONE1_COMMAND_H
#define MILE_STONE1_COMMAND_H

#include <string>
using namespace std;

// interface
class Command {
public:

    virtual void doCommand() = 0;
};


#endif //MILE_STONE1_COMMAND_H
