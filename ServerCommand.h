#ifndef MILE_STONE1_SERVERCOMMAND_H
#define MILE_STONE1_SERVERCOMMAND_H


#include <unordered_map>
#include <thread>
#include <mutex>
#include "Command.h"
#include "Observer.h"
#include "Notifier.h"
#include "ExpressionFactory.h"

class ServerCommand : public Command, public Observer {
    std::vector<int>* clientsSockfd = nullptr;
    std::unordered_map<std::string, int>* numsOfPathsNames = nullptr;
    std::unordered_map<int, double*>* valuesOfPaths = nullptr;
    std::vector<std::thread>* threads = nullptr;
protected:
    std::mutex* mtx = nullptr;
    ExpressionFactory* expressFactor = nullptr;
    Expression* hostExpress = nullptr;
    Expression *rateExpress = nullptr;
public:
    ServerCommand(std::unordered_map<std::string, int>* mapNames,
                  std::unordered_map<int, double*>* mapValues,
                  Notifier*,
                  std::vector<std::thread>*,
                  ExpressionFactory*,
                  std::mutex*);


    virtual ~ServerCommand() = 0;

    /**
     * the function open data server and send massagess.
     * @param v  - std::vector<std::string>.
     */
    void run();

    void doCommand(std::vector<std::string>& v) override;


    /**
     * The function get string with values, and add them to the map.
     *
     * @param buffer - string&.
     */
    int updateMap(const std::string& buffer);


    std::vector<int>* getClientSockfd() const{
        return clientsSockfd;
    }

    virtual int openServer(int host) = 0;
    virtual int connectToClient(int sockfd) = 0;
    virtual void readFromClient(int sockfd, unsigned rate) = 0;
};


#endif //MILE_STONE1_OPENSERVERCOMMAND_H
