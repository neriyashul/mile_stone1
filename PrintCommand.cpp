#include "PrintCommand.h"

using namespace std;

void PrintCommand::doCommand(vector<string> &v)  {
    if (v.empty()) {
        throw "wrong numbers of arguments";
    }

    for (string& s : v) {
        if (*s.begin() == '"' && *(s.end()-1) == '"') {
            s.erase(s.begin());
            s.erase(s.end() - 1);
            cout << s << endl;
            this->isString = true;
        } else  if (isString) {
            cout << s << endl;
        } else {
            if (this->expressFactor == nullptr) {
                throw "problem with incomming arguments";
            }
            Expression* e = expressFactor->expressionFromString(v).front();
            cout << e->calculate() << endl;
            delete(e);
        }
    }
}

