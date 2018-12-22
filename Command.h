#ifndef MILE_STONE1_COMMAND_H
#define MILE_STONE1_COMMAND_H

#include <string>
#include <vector>

using namespace std;

// interface
class Command {
public:

    virtual void doCommand(vector<string>&) = 0;
};


#endif //MILE_STONE1_COMMAND_H
