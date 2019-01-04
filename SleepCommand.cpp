#include "SleepCommand.h"

using namespace std;

void SleepCommand::doCommand(std::vector<std::string> &v)  {
    double time =
            this->sy->expressionFromString(v)->calculate();

    this_thread::sleep_for(
            chrono::milliseconds((unsigned) time));
}