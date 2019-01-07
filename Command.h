#ifndef MILE_STONE1_COMMAND_H
#define MILE_STONE1_COMMAND_H

#include <string>
#include <vector>



// interface
class Command {
public:
    virtual ~Command() = default;
    virtual void doCommand(std::vector<std::string>& v) = 0;
};


#endif //MILE_STONE1_COMMAND_H
