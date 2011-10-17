#ifndef NETWORKINPUTSTREAM_H
#define NETWORKINPUTSTREAM_H

#include "inputstream.h"
#include <string>

#define CHECKSTATUS() \
     if (checkStatus() < 0) { \
         throw new StreamException(new std::string("Network Error")); \
     }

class NetworkInputStream : public InputStream
{
    public:
        /** Default constructor */
        NetworkInputStream(int socket);
        /** Default destructor */
        virtual ~NetworkInputStream();

    public:
        virtual unsigned char readChar();
        /* Reads 2 bytes in the input (little endian order) */
        virtual int readInt ();
        /* Reads 4 bytes in the input (little endian order) */
        virtual long readLong ();
        /* Reads a 4 byte float in the input */
        virtual float readFloatIEEE ();
        /* Reads a 8 byte double in the input */
        virtual double readDoubleIEEE ();
        /* Read a chars */
        virtual char* readChars();
        virtual char* readChars(int length);

        virtual void closeStream();
        bool eof();
        int available();
        int waitAvailable(int timeout = 10);

        virtual std::string* readString();
        int setNonblocking();
    protected:
    private:
        int _socket;

    private:
        int checkStatus();
        int readData(void *buffer, int len);

};

#endif // NETWORKINPUTSTREAM_H
