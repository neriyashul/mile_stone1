//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_TCPCLIENT_H
#define MILE_STONE1_TCPCLIENT_H

#include "OpenClientCommand.h"

class OpenTcpClient : public OpenClientCommand {
public:
    /**
     * The function connect a client to some server.
     *
     * @param ip -  const char*.
     * @param host - const char*.
     * @return int.
     */
    int connectClient(const char* ip, const char* host) override;

    /**
     * The function gets sockdf, ask for string
     * and write it to the server.
     *
     * @param sockfd -  int.
     */
    void writeToServer(int) override;
};


#endif //MILE_STONE1_TCPCLIENT_H
