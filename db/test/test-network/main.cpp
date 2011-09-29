#include <iostream>
#include "networkservice.h"
#include "networkoutputstream.h"
#include "util.h"
#include "bsonoutputstream.h"
#include "bson.h"
#include "config.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "command.h"

#include <ctime>
#ifndef WINDOWS
#include <time.h>
#endif
#ifdef WINDOWS
#include <Windows.h>
#endif
#include <assert.h>
#include <math.h>

using namespace std;

#ifdef LINUX
timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
#endif

#ifdef WINDOWS
timeval diff(timeval start, timeval end)
{
	timeval temp;
	if ((end.tv_usec-start.tv_usec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_usec = 1000000+end.tv_usec-start.tv_usec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_usec = end.tv_usec-start.tv_usec;
	}
	return temp;
}
#endif

#ifdef WINDOWS
LARGE_INTEGER getFILETIMEoffset()
{
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime(&s, &f);
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart <<= 32;
    t.QuadPart |= f.dwLowDateTime;
    return (t);
}

int clock_gettime(int X, struct timeval *tv)
{
    LARGE_INTEGER           t;
    FILETIME            f;
    double                  microseconds;
    static LARGE_INTEGER    offset;
    static double           frequencyToMicroseconds;
    static int              initialized = 0;
    static BOOL             usePerformanceCounter = 0;

    if (!initialized) {
        LARGE_INTEGER performanceFrequency;
        initialized = 1;
        usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
        if (usePerformanceCounter) {
            QueryPerformanceCounter(&offset);
            frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
        } else {
            offset = getFILETIMEoffset();
            frequencyToMicroseconds = 10.;
        }
    }
    if (usePerformanceCounter) QueryPerformanceCounter(&t);
    else {
        GetSystemTimeAsFileTime(&f);
        t.QuadPart = f.dwHighDateTime;
        t.QuadPart <<= 32;
        t.QuadPart |= f.dwLowDateTime;
    }

    t.QuadPart -= offset.QuadPart;
    microseconds = (double)t.QuadPart / frequencyToMicroseconds;
    t.QuadPart = microseconds;
    tv->tv_sec = t.QuadPart / 1000000;
    tv->tv_usec = t.QuadPart % 1000000;
    return (0);
}
#endif

char* sendReceive(char* host, int port, int inserts) {
    int interval;
    #ifdef LINUX
    timespec ts1;
    timespec ts2;
    interval = CLOCK_PROCESS_CPUTIME_ID;
    #endif
    #ifdef WINDOWS
    struct timeval ts1;
    struct timeval ts2;
    interval = 0;
    #endif

    Logger* log = getLogger(NULL);

    NetworkOutputStream* out = new NetworkOutputStream();
    out->open(host, port);
    out->writeLong(1999);
    out->writeChars("1.2.3", 5);
    for (int x = 0; x < inserts; x++) {
        out->writeLong(1); // Command insert
        out->writeString(new std::string("myns")); // namespace
        BSONOutputStream* bsonOut = new BSONOutputStream(out);
        BSONObj* obj = new BSONObj();
        obj->add("name", "John");
        char temp[2000];
        memset(temp, 0, 2000);
        memset(temp, 'a', 1999);
        int len = strlen(temp);
        obj->add("content", temp);
        obj->add("last", "Smith");
        bsonOut->writeBSON(*obj);

    }
    cout << "Sending close connection command" << endl;
    out->writeInt(CLOSECONNECTION);
    cout << "all sent" << endl;
//    char rec[256];
//    bzero(rec, 256);
//    n = read(sockfd, rec, 255);
//    if (n < 0)
//        log->error("ERROR reading from socket");
    cout << "Ready to close the connection" << endl;
    sleep(10);
    cout << "Closing the connection" << endl;
    out->closeStream();

    delete(log);
    return 0;
}

void testMassiveInsert(int inserts) {
    int interval;
    #ifdef LINUX
    timespec ts1;
    timespec ts2;
    interval = CLOCK_PROCESS_CPUTIME_ID;
    #endif
    #ifdef WINDOWS
    struct timeval ts1;
    struct timeval ts2;
    interval = 0;
    #endif

    clock_gettime(interval, &ts1);
//    FileOutputStream fos("temp.txt", "wb+");

    sendReceive("localhost",1243, inserts);
//    fos.close();

    clock_gettime(interval, &ts2);

    #ifdef LINUX
    timespec etime = diff(ts1, ts2);
    double secs = etime.tv_sec + ((double)etime.tv_nsec / 1000000000.0);
    #else
    struct timeval etime = diff(ts1, ts2);
    double secs = etime.tv_sec + ((double)etime.tv_usec / 1000000.0);
    #endif

    cout<< "inserts " << inserts << ", secs: " << secs << endl;

    cout << "Throughput: " << (inserts / secs) << " ops." << endl;
    cout << "------------------------------------------------------------" << endl;
}

int main(int argc, char* args[])
{
//    NetworkService service;
//    service.start();
//
    int inserts;
    if (argc > 1) {
        cout << "Arg: " << args[1] << endl;
        inserts = atoi(args[1]);
    } else {
        inserts = 1;
    }
    cout << "Inserts " << inserts << endl;
    sleep(2);
    testMassiveInsert(inserts);

//    getchar();
//
//    service.stop();

    return 0;
}


