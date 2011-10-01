#include "networkoutputstream.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include <iostream>

using namespace std;

NetworkOutputStream::NetworkOutputStream()
{
}

NetworkOutputStream::~NetworkOutputStream()
{
    //dtor
}


/* Write 1 byte in the output */
void NetworkOutputStream::writeChar (unsigned char v)
{
    write(_socket, &v, 1);
}

/* Write 2 bytes in the output (little endian order) */
void NetworkOutputStream::writeInt (int v)
{
    unsigned char c = (v & 255);
    unsigned char c2= ((v >> 8) & 255);
    writeChar (c);
    writeChar (c2);
}

/* Write 4 bytes in the output (little endian order) */
void NetworkOutputStream::writeLong (long v)
{
    writeInt ((v) & 0xffff);
    writeInt ((v >> 16) & 0xffff);
}

/* Write a 4 byte float in the output */
void NetworkOutputStream::writeFloatIEEE (float v)
{
    write(_socket, &v, sizeof(v));
}

/* Write a 8 byte double in the output */
void NetworkOutputStream::writeDoubleIEEE (double v)
{
    write(_socket, &v, sizeof(v));
}

void NetworkOutputStream::writeChars(const char *text, int len) {
    writeLong(len);
    char buffer[1024];
    int pos = 0;
    while (pos < len) {
        int loops = 0;
        memset(buffer, 0, 1024);
        int size;
        if ((len-pos) > 1024) {
            size = 1024;
            memcpy(buffer, &(text[pos]), size);
        } else {
            size = len-pos;
            memcpy(buffer, &(text[pos]), size);
        }
        pos += size;
        int sent = 0;
        while ((sent < size) && (++loops < 100)) {
            sent += write(_socket, &buffer[sent], size - sent);
        }
        if (loops > 50) {
            cout << "Too many loops " << loops << endl;
        }
    }
//    write(_socket, text, len);
}

void NetworkOutputStream::writeString(const std::string* text) {
    if (text == NULL) {
        writeChars("", 0);
    } else {
        const char* c = text->c_str();
        int l = strlen(c);
        writeChars(c, l);
    }
}

int NetworkOutputStream::open(const char* hostname, int port)
{

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
//        log->error("ERROR opening socket");
        return NULL;
    }
    server = gethostbyname(hostname);
    if (server == NULL) {
//        log->error("ERROR, no such host\n");
        return NULL;
    }
    bzero((char *) & serv_addr, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
            (char *) & serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (sockaddr *) & serv_addr, sizeof (serv_addr)) < 0) {
//        log->error("ERROR connecting");
        return -1;
    }
    _socket = sockfd;
}

void NetworkOutputStream::closeStream() {
    close(_socket);
}
