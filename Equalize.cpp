#include <thread>
#include "Equalize.h"
using namespace std;

Equalize::Equalize(unordered_map<string, Var *> *vars,
                         ExpressionFactory *ef, bool *isNewMass,
                         string *massag, mutex *mtx) {
    variables = vars;
    isNewMassage = isNewMass;
    massage = massag;
    expressFactor = ef;
    clientMtx = mtx;
}


void Equalize::doCommand(vector<string> &args)  {
    if (args.size() < 2 && !this->name) {
        throw "wrong numbers of arguments";
    }
    // lock mutex.
    lock_guard<mutex> lock(*clientMtx);

    if (this->name == nullptr) {
        name = variables->at(args[0]);
        // delete the left var from the vector.
        args.erase(args.begin());
    }

    Expression* e = expressFactor->expressionFromString(args).front();
    double right = e->calculate();
    this->name->update(right);
    *this->massage = "set " + name->getPath() +  " " + to_string(right);
    //string f = *this->massage;
    *this->isNewMassage = true;
    //this_thread::sleep_for(chrono::milliseconds(200));
    delete(e);
}