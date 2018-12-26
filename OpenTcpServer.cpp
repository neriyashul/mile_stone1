#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include "OpenTcpServer.h"

/**
     * The function open new server.
     * @param host - int.
     * @return int - sockfd.
     */
int OpenTcpServer::openServer(int host) {
    int sockfd, portno;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = host;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    return sockfd;
}

/**
     * The function with until a client will connect in sockfd.
     * @param sockfd - int.
     * @return int - sockfd.
     */
int OpenTcpServer::connectToClient(int sockfd) {
    struct sockaddr_in cli_addr;
    int newsockfd, clilen;
    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    return newsockfd;
}

/**
     * The function write to client in the sockfd that gets.
     * @param sockfd - int.
     */
void OpenTcpServer::writeToClient(int sockfd) {
    /* start communicating */
    int n;
    char buffer[256];
    bzero(buffer,256);
    n = static_cast<int>(read(sockfd, buffer, 255));

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    printf("Here is the message: %s\n",buffer);

    /* Write a response to the client */
    n = static_cast<int>(write(sockfd, "I got your message\n", 18));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}