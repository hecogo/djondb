#include "networkclient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include "util.h"

char* sendReceive(char* host, int port, const char* command) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    Logger* log = getLogger(NULL);

    portno = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        log->error("ERROR opening socket");
        return NULL;
    }
    server = gethostbyname(host);
    if (server == NULL) {
        log->error("ERROR, no such host\n");
        return NULL;
    }
    bzero((char *) & serv_addr, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
            (char *) & serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (sockaddr *) & serv_addr, sizeof (serv_addr)) < 0) {
        log->error("ERROR connecting");
        return NULL;
    }

    n = write(sockfd, command, strlen(command));
    if (n < 0) {
        log->error("ERROR writing to socket");
        return NULL;
    }
    char rec[256];
    bzero(rec, 256);
    n = read(sockfd, rec, 255);
    if (n < 0)
        log->error("ERROR reading from socket");
    close(sockfd);

    delete(log);
    return rec;
}

Response* sendReceive(char* host, int port, Request* req) {
    const char* requestData = req->toCharArray();
    char* result = sendReceive(host, port, requestData);
    Response* response = new Response(new string(result));
    return response;
}

