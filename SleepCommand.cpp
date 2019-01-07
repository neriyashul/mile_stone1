#include "SleepCommand.h"

using namespace std;

void SleepCommand::doCommand(std::vector<std::string> &v)  {
    if (v.empty()) {
        throw "wrong numbers of arguments";
    }
    Expression* e = this->ef->expressionFromString(v).front();
    double time = e->calculate();
    delete(e);

    this_thread::sleep_for(
            chrono::milliseconds((unsigned) time));
}