#ifndef MILE_STONE1_TCPSERVERCOMMAND_H
#define MILE_STONE1_TCPSERVERCOMMAND_H

#define STR_EXIT "exit"

#include <mutex>
#include "ServerCommand.h"

class TcpServer : public ServerCommand {
    std::mutex* mtx;
public:
    // constructor.
    TcpServer(std::unordered_map<std::string,int>* mapNames
                 ,std::unordered_map<int, double>* mapValues,
                 std::mutex* mtxServer) : ServerCommand(mapNames, mapValues){
        mtx = mtxServer;
    }

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
    void readFromClient(int sockfd, unsigned rate) override;
};


#endif //MILE_STONE1_OPENTCPSERVERCOMMAND_H
