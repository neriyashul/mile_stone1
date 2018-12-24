//
// Created by neriya on 12/24/18.
//

#ifndef MILE_STONE1_OPENSERVERCOMMAND_H
#define MILE_STONE1_OPENSERVERCOMMAND_H


#include "Command.h"
#include "Expression.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>

class OpenServerCommand : public Command {
    vector<int> clientsSockfd;
public:
    virtual void doCommand(vector<string>& v) {
        if (v.size() != 2) {
            throw "wrong in the numbers of arguments";
        }
        // use [] because there is 2 arguments.
        //Expression *e = new;
        //clientsSockfd.push_back(openServer(v[0].c_str(), v[1].c_str()));
    }

    vector<int> getClientSockfd() const{
        return clientsSockfd;
    }

    virtual int openServer(int host) = 0;
    virtual int connectToClient(int sockfd) = 0;
    virtual void writeToClient(int sockfd) = 0;
};


#endif //MILE_STONE1_OPENSERVERCOMMAND_H
