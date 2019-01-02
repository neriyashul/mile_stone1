#include "ServerCommand.h"

void ServerCommand::doCommand(std::vector<std::string> &v)  {
    if (v.size() != 2) {
        throw "wrong numbers of arguments";
    }
    // use [] because there is 2 arguments.
    int host = std::stoi(v[0]);
    auto rate = (unsigned) std::stoi(v[1]);
    int sockfd = connectToClient(openServer(host));
    readFromClient(sockfd, rate);
    clientsSockfd->push_back(sockfd);
}


/**
     * The function get string with values, and add them to the map.
     *
     * @param buffer - string&.
     */
void ServerCommand::updateMap(const std::string &buffer)  {
    if (valuesOfPathsNums == nullptr) {
        throw "there is no allocated map";
    }
    size_t indexStart = 0;
    size_t indexEnd = 0;
    unsigned numInMap = 1;
    indexEnd = buffer.find(',');

    // add to the map the numbers which inserted in the buffer
    while (indexEnd != std::string::npos) {
        valuesOfPathsNums->at(numInMap) = std::stod(buffer.substr(indexStart, indexEnd - indexStart));
        ++numInMap;
        indexStart = indexEnd + 1;
        indexEnd = buffer.find(',');
    }
    // add the last number to the map
    valuesOfPathsNums->at(numInMap) = std::stod(buffer.substr(indexStart));
}