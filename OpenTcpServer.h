//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_OPENTCPSERVER_H
#define MILE_STONE1_OPENTCPSERVER_H


#include "OpenServerCommand.h"

class OpenTcpServer : public OpenServerCommand {
    /**
     * The function open new server.
     * @param host - int.
     * @return int - sockfd.
     */
    virtual int openServer(int host);

    /**
     * The function with until a client will connect in sockfd.
     * @param sockfd - int.
     * @return int - sockfd.
     */
    virtual int connectToClient(int sockfd);

    /**
     * The function write to client in the sockfd that gets.
     * @param sockfd - int.
     */
    virtual void writeToClient(int sockfd);
};


#endif //MILE_STONE1_OPENTCPSERVER_H
