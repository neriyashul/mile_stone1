#include "ServerCommand.h"

void ServerCommand::doCommand(std::vector<std::string> &v)  {
    if (v.size() != 2) {
        throw "wrong numbers of arguments";
    }
    // use [] because there is 2 arguments.
    int host = std::stoi(v[0]);
    auto rate = (unsigned) std::stoi(v[1]);
    int sockfd = connectToClient(openServer(host));
    //clientsSockfd->push_back(sockfd);
    readFromClient(sockfd, rate);
}


/**
     * The function get string with values, and add them to the map.
     *
     * @param buffer - string&.
     */
int ServerCommand::updateMap(const std::string &buffer)  {

    if (valuesOfPathsNums == nullptr || valuesOfPathsNums->empty()) {
        return 1;
    }

    unsigned numInMap = 1;
    std::size_t indexStart = 0;
    std::size_t indexEnd = 0;

    // add to the map the numbers which inserted in the buffer
    while (!buffer.empty() && indexEnd != std::string::npos) {
        indexEnd = buffer.find(',', indexStart);
        double d = std::stod(buffer.substr(indexStart, indexEnd - indexStart));
        valuesOfPathsNums->at(numInMap) = d;
        ++numInMap;
        indexStart = indexEnd + 1;
    }

    return 0;
}