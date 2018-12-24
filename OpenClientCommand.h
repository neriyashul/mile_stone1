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
    /**
     * The function open client.
     *
     * @param v -  vector<string>&.
     */
    virtual void doCommand(vector<string>& v) {
        if (v.size() != 2) {
            throw "wrong in the numbers of arguments";
        }
        // use [] because there is 2 arguments.
        clientSockfd = connectClient(v[0].c_str(), v[1].c_str());
    }

    /**
     * The function connect a client to some server.
     *
     * @param ip -  const char*.
     * @param host - const char*.
     * @return int.
     */
    virtual int connectClient(const char* ip, const char* host) = 0;

    /**
     * The function return the sockfd.
     *
     * @param ip -  const char*.
     * @param host - const char*.
     * @return int.
     */
    int getSockfd() const {

        return clientSockfd;
    }

    /**
     * The function gets sockdf, ask for string
     * and write it to the server.
     *
     * @param sockfd -  int.
     */
    virtual void writeToServer(int sockfd) = 0;
};


#endif //MILE_STONE1_OPENSERVERCOMMAND_H
