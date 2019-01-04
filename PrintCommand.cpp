#include "PrintCommand.h"

void PrintCommand::doCommand(std::vector<std::string> &v)  {
    for (std::string& s : v) {
        if (*s.begin() == '"' && *(s.end()-1) == '"') {
            s.erase(s.begin());
            s.erase(s.end() - 1);
            std::cout << s;
        } else {
            if (this->sy == nullptr) {
                throw "problem with incomming arguments";
            }
            std::cout << sy->expressionFromString(v)->calculate();
        }
    }
}

