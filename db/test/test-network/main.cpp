#include <iostream>
#include "networkservice.h"
#include "networkoutputstream.h"
#include "util.h"
#include "bsonoutputstream.h"
#include "bson.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <string>
#include <stdio.h>

using namespace std;


char* sendReceive(char* host, int port) {
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

    NetworkOutputStream* out = new NetworkOutputStream(sockfd);
    out->writeChars("1.2.3", 5);
    out->writeInt(1); // Command insert
    out->writeString(new std::string("myns")); // namespace
    BSONOutputStream* bsonOut = new BSONOutputStream(out);
    BSONObj* obj = new BSONObj();
    obj->add("name", new std::string("test"));
    bsonOut->writeBSON(*obj);

//    char rec[256];
//    bzero(rec, 256);
//    n = read(sockfd, rec, 255);
//    if (n < 0)
//        log->error("ERROR reading from socket");
    close(sockfd);

    delete(log);
    return 0;
}

int main()
{
    NetworkService service;
    service.start();

    sendReceive("localhost",1243);

    getchar();
    return 0;
}


