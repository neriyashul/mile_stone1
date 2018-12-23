//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_TCPCLIENT_H
#define MILE_STONE1_TCPCLIENT_H

#include "OpenClientCommand.h"

class OpenTcpClient : public OpenClientCommand {
public:
    int connectClient(const char* ip, const char* host) override;
    void writeToServer(int) override;
};


#endif //MILE_STONE1_TCPCLIENT_H
