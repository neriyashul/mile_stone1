//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_OPENSERVERCOMMAND_H
#define MILE_STONE1_OPENSERVERCOMMAND_H

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include "Command.h"

class OpenClientCommand : public Command {
    int clientSockfd = -1;
public:
    virtual void doCommand(vector<string>& v) {
        if (v.size() != 2) {
            throw "wrong in the numbers of arguments";
        }
        // use [] because there is 2 arguments.
        clientSockfd = connectClient(v[0].c_str(), v[1].c_str());
    }

    virtual int connectClient(const char* ip, const char* host) = 0;

    int getSockfd() const {

        return clientSockfd;
    }

    virtual void writeToServer(int) = 0;
};


#endif //MILE_STONE1_OPENSERVERCOMMAND_H
