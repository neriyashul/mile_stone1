//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_OPENTCPSERVERCOMMAND_H
#define MILE_STONE1_OPENTCPSERVERCOMMAND_H


#include "OpenServerCommand.h"

class OpenTcpServer : public OpenServerCommand {
public:
    /**
     * The function open new server.
     * @param host - int.
     * @return int - sockfd.
     */
    int openServer(int host) override;

    /**
     * The function with until a client will connect in sockfd.
     * @param sockfd - int.
     * @return int - sockfd.
     */
    int connectToClient(int sockfd) override;

    /**
     * The function write to client in the sockfd that gets.
     * @param sockfd - int.
     */
    void writeToClient(int sockfd) override;
};


#endif //MILE_STONE1_OPENTCPSERVERCOMMAND_H
