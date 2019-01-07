#include "ClientCommand.h"
using namespace std;
ClientCommand::ClientCommand(bool *isMassage,
        string *mas, mutex *mtx,Notifier *n,
        vector<thread> *allThreads,ExpressionFactory *ef)  {
    isNewMassage = isMassage;
    massage = mas;
    clientMtx = mtx;
    n->addObserver(this);
    threads = allThreads;
    expressFactor = ef;
}

void ClientCommand::run(){
    this->clientSockfd = connectClient();
    writeToServer(clientSockfd);
}

void ClientCommand::doCommand(vector<string> &v)  {
    if (v.size() < 2) {
        throw "wrong numbers of arguments";
    }
    this->ip = v[0];

    // remove the ip from v.
    v.erase(v.begin());

    this->host = this->expressFactor
                     ->expressionFromString(v).front();

    threads->push_back(thread(&ClientCommand::run,this));
    this_thread::sleep_for(chrono::milliseconds(300));
}