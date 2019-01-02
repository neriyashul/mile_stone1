#ifndef MILE_STONE1_SERVERCOMMAND_H
#define MILE_STONE1_SERVERCOMMAND_H


#include <unordered_map>
#include "Command.h"

class ServerCommand : public Command {
    std::vector<int>* clientsSockfd = nullptr;
    std::unordered_map<std::string, int>* numsOfPathsNames = nullptr;
    std::unordered_map<int, double>* valuesOfPathsNums = nullptr;
public:
    ServerCommand(std::unordered_map<std::string, int>* mapNames,
                       std::unordered_map<int, double>* mapValues) {
        this->numsOfPathsNames = mapNames;
        this->valuesOfPathsNums = mapValues;
    }

    void doCommand(std::vector<std::string>& v) override;


    /**
     * The function get string with values, and add them to the map.
     *
     * @param buffer - string&.
     */
    void updateMap(const std::string& buffer);

    void setFlightName(std::string& name) {
        // if not already in the map ,add it.
        (*numsOfPathsNames)[name] = (int) numsOfPathsNames->size();
    }

    int getFlightName(std::string& name) const {
        return numsOfPathsNames->at(name);
    }

    void setFlightValue(int name, double value) {
        // if not already in the map ,add it.
        (*valuesOfPathsNums)[name] = value;
    }

    double getFlightValue(int name) const {
        return valuesOfPathsNums->at(name);
    }



    std::vector<int>* getClientSockfd() const{
        return clientsSockfd;
    }

    virtual int openServer(int host) = 0;
    virtual int connectToClient(int sockfd) = 0;
    virtual void readFromClient(int sockfd, unsigned rate) = 0;
};


#endif //MILE_STONE1_OPENSERVERCOMMAND_H
