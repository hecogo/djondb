#include <iostream>
#include <dbcontroller.h>
#include <util.h>
#include <config.h>
#include <ctime>
#ifndef WINDOWS
#include <time.h>
#endif
#ifdef WINDOWS
#include <Windows.h>
#endif
#include "bson.h"

using namespace std;

DBController controller;

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

int testInsert(BSONObj* o) {
    controller.insert("sp1.customer", o);
}

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

int testMassiveInsert(int inserts) {
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

    for (int x = 0; x < inserts; x++) {
        BSONObj* obj = new BSONObj();
        obj->add("name", "John");
        obj->add("last", "Smith");
        testInsert(obj);
    }

    clock_gettime(interval, &ts2);

    #ifdef LINUX
    timespec etime = diff(ts1, ts2);
    double secs = etime.tv_sec + ((double)etime.tv_nsec / 1000000000.0);
    #else
    struct timeval etime = diff(ts1, ts2);
    double secs = etime.tv_sec + ((double)etime.tv_usec / 1000000.0);
    #endif

    cout<< "inserts " << inserts << ", secs: " << secs << endl;
}

int main()
{
    BSONObj* o = new BSONObj();
    o->add("name", "John");
    o->add("last", "Crossley");
    testInsert(o);
    delete(o);
//
//    testMassiveInsert(1000);
//    testMassiveInsert(10000);
//    testMassiveInsert(100000);
//    testMassiveInsert(1000000);
//    testMassiveInsert(10000000);

    controller.close("sp1.customer");
    return 0;
}
