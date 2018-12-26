//
// Created by neriya on 12/24/18.
//

#ifndef MILE_STONE1_OPENSERVERCOMMAND_H
#define MILE_STONE1_OPENSERVERCOMMAND_H


#include "Command.h"

class OpenServerCommand : public Command {
    vector<int> clientsSockfd;
public:
    void doCommand(vector<string>& v) override {
        if (v.size() != 2) {
            throw "wrong numbers of arguments";
        }
        // use [] because there is 2 arguments.
        int host = stoi(v[0]);
        int rate = stoi(v[1]);
        int sockfd = connectToClient(openServer(host));
        writeToClient(sockfd);
        clientsSockfd.push_back(sockfd);
    }

    vector<int> getClientSockfd() const{
        return clientsSockfd;
    }

    virtual int openServer(int host) = 0;
    virtual int connectToClient(int sockfd) = 0;
    virtual void writeToClient(int sockfd) = 0;
};


#endif //MILE_STONE1_OPENSERVERCOMMAND_H
