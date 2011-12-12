#include "networkoutputstream.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <iostream>

using namespace std;

NetworkOutputStream::NetworkOutputStream()
{
}

NetworkOutputStream::~NetworkOutputStream()
{
    //dtor
}

NetworkOutputStream::NetworkOutputStream(int socket)
{
    _socket = socket;
}

NetworkOutputStream::NetworkOutputStream(const NetworkOutputStream& origin) {
    this->_socket = origin._socket;
}


/* Write 1 byte in the output */
void NetworkOutputStream::writeChar (unsigned char v)
{
    send(_socket, &v, 1, MSG_NOSIGNAL);
//    write(_socket, &v, 1);
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
    send(_socket, &v, sizeof(v), MSG_NOSIGNAL);
//    write(_socket, &v, sizeof(v));
}

/* Write a 8 byte double in the output */
void NetworkOutputStream::writeDoubleIEEE (double v)
{
    send(_socket, &v, sizeof(v), MSG_NOSIGNAL);
//    write(_socket, &v, sizeof(v));

}

void NetworkOutputStream::writeChars(const char *text, int len) {
    writeLong(len);
    char buffer[1024];
    int pos = 0;
    while (pos < len) {
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
        while (sent < size) {
            sent += send(_socket, &buffer[sent], size - sent, MSG_NOSIGNAL);
//            sent += write(_socket, &buffer[sent], size - sent);
        }
    }
//    write(_socket, text, len);
}

void NetworkOutputStream::writeString(const std::string& text) {
    const char* c = text.c_str();
    int l = strlen(c);
    writeChars(c, l);
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
        return -1;
    }
    server = gethostbyname(hostname);
    if (server == NULL) {
//        log->error("ERROR, no such host\n");
        return -1;
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

    return sockfd;
}

void NetworkOutputStream::closeStream() {
    shutdown(_socket, SHUT_RDWR);
    close(_socket);
}

int NetworkOutputStream::setNonblocking() {
    int flags;
    /* If they have O_NONBLOCK, use the Posix way to do it */
#if defined(O_NONBLOCK)
    /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
    if (-1 == (flags = fcntl(_socket, F_GETFL, 0)))
        flags = 0;
    return fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
#else
    /* Otherwise, use the old way of doing it */
    flags = 1;
    return ioctl(_socket, FIOBIO, &flags);
#endif
}

int NetworkOutputStream::disableNagle() {
    /* Disable the Nagle (TCP No Delay) algorithm */

    int flag = 1;

    int ret = setsockopt( _socket, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag) );
    return ret;
}
