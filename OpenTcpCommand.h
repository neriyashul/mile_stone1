//
// Created by neriya on 12/23/18.
//

#ifndef MILE_STONE1_OPENTCPCLIENTCOMMAND_H
#define MILE_STONE1_OPENTCPCLIENTCOMMAND_H

#include "OpenClientCommand.h"

class OpenTcpCommand : public OpenClientCommand {

        public:

        /**
        * The function connect a client to some server.
        *
        * @param ip -  const char*.
        * @param host - const char*.
        * @return int.
        */
        virtual int connectClient(const char* ip, const char* host);

        /**
         * The function gets sockdf, ask for string
         * and write it to the server.
         *
         * @param sockfd -  int.
         */
        virtual void writeToServer(int);
};


#endif //MILE_STONE1_OPENTCPCLIENTCOMMAND_H
