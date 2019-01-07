#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include "TcpServer.h"

using namespace std;

/**
     * The function open new server.
     * @param host - int.
     * @return int - sockfd.
     */
int TcpServer::openServer(int host) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;

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
int TcpServer::connectToClient(int sockfd) {
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
 * The function return if the thread should be done.
 * The function shoudn't gets
 * any argument until the thread done.
 */
bool isEnd(const string s = "") {
    static bool a = false;
    if (s == "end") {
        a = true;
    }
    return a;
}


/**
     * The function write to client in the sockfd that gets.
     * @param sockfd - int.
     */
void TcpServer::readFromClient(int sockfd, unsigned rate) {
    // time: rate per second (1000 millisecond):
    rate = (1/rate * 1000);

    /* start communicating */
    int n;
    char buffer [256] ;
    bzero(buffer,256);
    while (true) {
        n = static_cast<int>(read(sockfd, buffer, 255));
        if (!strcmp(buffer, STR_EXIT)) {
            return;
        }

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        this_thread::sleep_for(chrono::milliseconds(rate));

        // lock mutex.
        lock_guard<mutex> lock(*mtx);
        if(isEnd()) {
            return;
        }
        updateMap(buffer);
    }
}

/**
 * the function close the thread.
 */
void TcpServer::finish() {
    // lock mutex.
    lock_guard<mutex> lock(*mtx);
    isEnd("end");
}