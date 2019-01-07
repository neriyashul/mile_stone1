#include "ServerCommand.h"

using namespace std;

ServerCommand::ServerCommand(unordered_map<string, int> *mapNames,
                             unordered_map<int, double*> *mapValues,
                             Notifier *notifier,
                             vector<thread> *allThreads,
                             ExpressionFactory* expressionFactor,
                             std::mutex* mtxServer) {
    this->numsOfPathsNames = mapNames;
    this->valuesOfPaths = mapValues;
    notifier->addObserver(this);
    this->threads = allThreads;
    this->expressFactor = expressionFactor;
    this->mtx = mtxServer;
}


ServerCommand::~ServerCommand() {
    delete(hostExpress);
    delete(rateExpress);
}

void ServerCommand::run() {
    double host = hostExpress->calculate();
    auto rate = (unsigned) rateExpress->calculate();
    int sockfd = connectToClient(
            openServer(static_cast<int>(host)));
    threads->push_back(thread(
            &ServerCommand::readFromClient,this, sockfd, rate));
    this_thread::sleep_for(chrono::milliseconds(300));
}

void ServerCommand::doCommand(vector<string> &v)  {
    vector<Expression*> expressions;
    expressions = this->expressFactor->expressionFromString(v);

    if (expressions.size() != 2) {
        throw "wrong numbers of arguments";
    }
    this->hostExpress = expressions[0];
    this->rateExpress = expressions[1];

    run();
}


/**
     * The function get string with values, and add them to the map.
     *
     * @param buffer - string&.
     */
int ServerCommand::updateMap(const string &buffer)  {

    if (valuesOfPaths == nullptr || valuesOfPaths->empty()) {
        return 1;
    }

    unsigned numInMap = 1;
    size_t indexStart = 0;
    size_t indexEnd = 0;

    // add to the map the numbers which inserted in the buffer
    while (!buffer.empty() && indexEnd != string::npos) {
        indexEnd = buffer.find(',', indexStart);
        double d = stod(buffer.substr(indexStart, indexEnd - indexStart));
        *valuesOfPaths->at(numInMap) = d;
        ++numInMap;
        indexStart = indexEnd + 1;
    }

    return 0;
}