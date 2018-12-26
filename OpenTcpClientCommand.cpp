//
// Created by neriya on 12/23/18.
//

#include "OpenTcpClientCommand.h"

/**
     * The function connect a client to some server.
     *
     * @param ip -  const char*.
     * @param host - const char*.
     * @return int.
     */
int OpenTcpCommand::connectClient(const char *ip, const char *host) {

    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = atoi(host);

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(ip);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    return sockfd;
}

/**
     * The function gets sockdf, ask for string
     * and write it to the server.
     *
     * @param sockfd -  int.
     */
void OpenTcpCommand::writeToServer(int sockfd)  {
    /* ask for a message from the user, this message
       * will be read by server
    */
    if (sockfd < 0) {
        throw "there is no connection to server";
    }
    char buffer[256];
    while (strcmp(buffer, "exit") != 0) {
        printf("Please enter the message: ");

        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        strcat(buffer, "\r\n");

        /* Send message to the server */
        int n = write(sockfd, buffer, strlen(buffer));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        /* Now read server response */
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        printf("%s\n", buffer);
    }
}