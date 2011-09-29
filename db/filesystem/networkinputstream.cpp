#include "networkinputstream.h"

#include "defs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/ioctl.h>

NetworkInputStream::NetworkInputStream(int clientSocket)
{
    _socket = clientSocket;
}

NetworkInputStream::~NetworkInputStream() {
    closeStream();
}

unsigned char NetworkInputStream::readChar() {
    unsigned char v;
    readData(&v, 1);
    return v;
}

/* Reads 2 bytes in the input (little endian order) */
int NetworkInputStream::readInt () {
    int v = readChar() | readChar() << 8;
    return v;
}

/* Reads 4 bytes in the input (little endian order) */
long NetworkInputStream::readLong () {
    long v = readInt() | readInt() << 16;

    return v;
}

/* Reads a 4 byte float in the input */
float NetworkInputStream::readFloatIEEE () {
    float f;
    readData(&f, sizeof(f));
    return f;
}

/* Reads a 8 byte double in the input */
double NetworkInputStream::readDoubleIEEE () {
    double d;
    readData(&d, sizeof(d));
    return d;
}

/* Read a chars */
char* NetworkInputStream::readChars() {
    int len = readInt();
    char* res = readChars(len);
    return res;
}

std::string* NetworkInputStream::readString() {
    char* c = readChars();
    std::string* res = new std::string(c);
    free(c);
    return res;
}

char* NetworkInputStream::readChars(int length) {
    char* res = (char*)malloc(length+1);
    memset(res, 0, length+1);
    readData(res, length);
    return res;
}

bool NetworkInputStream::eof() {
    return false;
}

void NetworkInputStream::closeStream() {
    close(_socket);
}

int NetworkInputStream::checkStatus() {
    return 0;
}

int NetworkInputStream::available() {
    size_t nbytes = 0;
    if ( ioctl(_socket, FIONREAD, (char*)&nbytes) < 0 )  {
            fprintf(stderr, "%s - failed to get byte count on socket.\n", __func__);
            return -1;
    }
    return nbytes;
}

int NetworkInputStream::readData(void* data, int len) {
    CHECKSTATUS()
    // wait until a data is available to be readed
    while (waitAvailable(1) < len);

    int readed = recv(_socket, data, len, 0);
    return readed;
}

int NetworkInputStream::waitAvailable(int timeout) {
    fd_set read;
    FD_ZERO(&read);
    FD_SET(_socket, &read);
    timeval val;
    val.tv_sec = timeout;
    val.tv_usec = 0;
    int result = select(_socket + 1, &read, NULL, NULL, &val);

    if (result < 0) {
        closeStream();
        return -1;
    }
    return available();
}
