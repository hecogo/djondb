#include "networkoutputstream.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

NetworkOutputStream::NetworkOutputStream(int socket)
{
    _socket = socket;
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
    writeInt(len);
    write(_socket, text, len);
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

