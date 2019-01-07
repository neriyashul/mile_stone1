#ifndef MILE_STONE1_CLIENTCOMMAND_H
#define MILE_STONE1_CLIENTCOMMAND_H

#include <cstdio>
#include <cstdlib>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <cstring>
#include <mutex>
#include <thread>
#include "Command.h"
#include "Observer.h"
#include "Notifier.h"
#include "ExpressionFactory.h"

class ClientCommand : public Command, public Observer {
protected:
    int clientSockfd = -1;
    bool* isNewMassage;
    std::string* massage;
    std::mutex* clientMtx;
    std::vector<std::thread>* threads;
    ExpressionFactory* expressFactor;
    Expression* host;
    std::string ip;
public:
    ClientCommand(bool* isMassage, std::string* mas,
            std::mutex* mtx, Notifier* n,
            std::vector<std::thread>* allThreads,
            ExpressionFactory* ef);

    ~ClientCommand() override {
        delete host;
    }
    /**
     * The function open client.
     *
     * @param v -  vector<string>&.
     */
    void doCommand(std::vector<std::string>& v) override;

    /**
     * the function open server and gets massagess.
     * @param v  - std::vector<std::string>.
     */
    void run();

    /**
     * The function connect a client to some server.
     *
     * @param ip -  const char*.
     * @param host - const char*.
     * @return int.
     */
    virtual int connectClient() = 0;


    /**
     * The function gets sockdf, ask for string
     * and write it to the server.
     *
     * @param sockfd -  int.
     */
    virtual void writeToServer(int sockfd) = 0;


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
};


#endif //MILE_STONE1_OPENSERVERCOMMAND_H
