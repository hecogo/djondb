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
#include <assert.h>

const int STREAM_BUFFER_SIZE = 100000;

NetworkInputStream::NetworkInputStream(int clientSocket)
{
    _socket = clientSocket;
    _buffer = (char*) malloc(STREAM_BUFFER_SIZE);
    _bufferPos = 0;
    _bufferSize = 0;
    _open = true;
}

NetworkInputStream::NetworkInputStream(const NetworkInputStream& orig) {
    _buffer = orig._buffer;
    this->_bufferPos = orig._bufferPos;
    this->_bufferSize = orig._bufferSize;
    this->_socket = orig._socket;
}

NetworkInputStream::~NetworkInputStream() {
    free (_buffer);
    assert(_bufferPos == _bufferSize);
//    closeStream();
}

unsigned char NetworkInputStream::readChar() {
    unsigned char v;
    readData(&v, 1);
    return v;
}

/* Reads 2 bytes in the input (little endian order) */
int NetworkInputStream::readInt () {
    unsigned char c1 = readChar();
    unsigned char c2 = readChar();
    int v = c1 | c2 << 8;
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
    int len = readLong();
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
    assert(strlen(res) == length);
    return res;
}

bool NetworkInputStream::eof() {
    return false;
}

void NetworkInputStream::closeStream() {
    close(_socket);
    _open = false;
}


bool NetworkInputStream::isClosed() {
    checkStatus();
    return !_open;
}

int NetworkInputStream::checkStatus() {
    if (_open) {
        int res = waitAvailable(10);
        if (res < 0) {
            closeStream();
        }
        return res;
    }
    return 0;
}

int NetworkInputStream::available() {
    int available = (_bufferSize - _bufferPos);
    return available;
//    size_t nbytes = 0;
//    if ( ioctl(_socket, FIONREAD, (char*)&nbytes) < 0 )  {
//            fprintf(stderr, "%s - failed to get byte count on socket.\n", __func__);
//            return -1;
//    }
//    return nbytes;
}

int NetworkInputStream::readData(void* data, int len) {
     if (checkStatus() < 0) {
         return -1;
     }
    // wait until a data is available to be readed
    int readed = 0;
    while (readed < len) {
        if (waitAvailable(10) < 0) {
            assert(false);
        }
        int read = (len - readed);
        if ((_bufferSize - _bufferPos) < read) {
            read = _bufferSize - _bufferPos;
        }
        memcpy(data + readed, _buffer + _bufferPos, read);
        _bufferPos += read;
//        int read = recv(_socket, data, len, 0);
//        // the connection could be closed
//        assert(read != 0);
        readed += read;
    }

//    char buffer[1024];
//    int total = 0;
//    int bytesleft = len;
//    while (true) {
//        int readed = recv(_socket, buffer, bytesleft, 0);
//        total += readed;
//        bytesleft -= readed;
//        if (total == len) {
//            break;
//        }
//    }
    if (len == 1999) {
        if (((char*)data)[1998] != 'a') {
            cout << "Hey!!!!" << endl;
        }
    }

    return readed;
}

int NetworkInputStream::waitAvailable(int timeout) {
    if (_bufferPos >= _bufferSize) {
        int result = fillBuffer(timeout);
        return result;
    }
    return 0;
}

int NetworkInputStream::setNonblocking() {
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

int NetworkInputStream::fillBuffer(int timeout) {
    memset(_buffer, 0, STREAM_BUFFER_SIZE);

    fd_set read;
    FD_ZERO(&read);
    FD_SET(_socket, &read);
    timeval val;
    val.tv_sec = timeout;
    val.tv_usec = 0;
    int result = select(_socket + 1, &read, NULL, NULL, &val);

    assert(result >= 0);
    if (result < 0) {
        closeStream();
        return -1;
    }
    int readed = recv(_socket, _buffer, STREAM_BUFFER_SIZE, 0);
    if (readed == 0) {
        // the other end closed the connection
        return -1;
    }
    _bufferPos = 0;
    _bufferSize = readed;
    return 0;
}
