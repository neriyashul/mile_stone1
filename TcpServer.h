#ifndef MILE_STONE1_TCPSERVERCOMMAND_H
#define MILE_STONE1_TCPSERVERCOMMAND_H

#define STR_EXIT "exit"

#include <mutex>
#include "ServerCommand.h"
#include "Notifier.h"

class TcpServer : public ServerCommand {
public:
    // constructor.
    TcpServer(std::unordered_map<std::string,int>* mapNames
                 ,std::unordered_map<int, double*>* mapValues,
                 std::mutex* mtxServer, Notifier* n,
                 std::vector<std::thread>* threads,
                 ExpressionFactory* ExpressFactor)
                   : ServerCommand(mapNames, mapValues, n,
                           threads, ExpressFactor, mtxServer){
    }

    ~TcpServer() override = default;

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

    void finish() override;
};


#endif //MILE_STONE1_OPENTCPSERVERCOMMAND_H
