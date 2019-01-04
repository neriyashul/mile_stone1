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
#include "Command.h"
#include "Observer.h"
#include "Notifier.h"

class ClientCommand : public Command, public Observer {
protected:
    bool* isNewMassage;
    std::string* massage;
    int clientSockfd = -1;
    std::mutex* clientMtx;
public:
    ClientCommand(bool* isMassage, std::string* mas, std::mutex* mtx, Notifier& n) {
        isNewMassage = isMassage;
        massage = mas;
        clientMtx = mtx;
        n.addObserver(this);
    }

    /**
     * The function open client.
     *
     * @param v -  vector<string>&.
     */
    void doCommand(std::vector<std::string>& v) override {
        if (v.size() != 2) {
            throw "wrong numbers of arguments";
        }
        // use [] because there is 2 arguments.
        this->clientSockfd = connectClient(v[0].c_str(), v[1].c_str());
        writeToServer(clientSockfd);
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
