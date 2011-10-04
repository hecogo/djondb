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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "fileoutputstream.h"
#include "fileinputstream.h"

using namespace std;

DBController controller;

std::vector<std::string*> __ids;

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

int testInsert(boost::shared_ptr<BSONObj> o) {
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
    interval = CLOCK_REALTIME;//CLOCK_PROCESS_CPUTIME_ID;
    #endif
    #ifdef WINDOWS
    struct timeval ts1;
    struct timeval ts2;
    interval = 0;
    #endif

    clock_gettime(interval, &ts1);
    FileOutputStream fos("temp.txt", "wb+");

    for (int x = 0; x < inserts; x++) {
        boost::shared_ptr<BSONObj> obj(new BSONObj());
        obj->add("name", "John");
        char temp[700];
        memset(temp, 0, 699);
        memset(temp, 'a', 700);
        obj->add("content", temp);
        obj->add("last", "Smith");
        testInsert(obj);

        int test = rand() % 10;
        if (test > 5) {
            __ids.push_back(new std::string(obj->getString("_id")->c_str()));
            fos.writeString(obj->getString("_id").get());
        }
        if ((x % 1000000) == 0) {
            clock_gettime(interval, &ts2);

            #ifdef LINUX
            timespec etime = diff(ts1, ts2);
            double secs = etime.tv_sec + ((double)etime.tv_nsec / 1000000000.0);
            #else
            struct timeval etime = diff(ts1, ts2);
            double secs = etime.tv_sec + ((double)etime.tv_usec / 1000000.0);
            #endif

            cout<< "inserts " << x << ", secs: " << secs << endl;

            cout << "Throughput: " << (x / secs) << " ops." << endl;
        }
    }
    fos.close();

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

void testFinds() {
   int interval;
    #ifdef LINUX
    timespec ts1;
    timespec ts2;
    interval = CLOCK_REALTIME;
    #endif
    #ifdef WINDOWS
    struct timeval ts1;
    struct timeval ts2;
    interval = 0;
    #endif

    clock_gettime(interval, &ts1);

    for (std::vector<string*>::iterator i = __ids.begin(); i != __ids.end(); i++) {
        boost::shared_ptr<string> id(*i);

        boost::shared_ptr<BSONObj> obj(new BSONObj());
        obj->add("_id", id);
        boost::shared_ptr<BSONObj> res = controller.findFirst("sp1.customer", obj);
        std::string* id2 = res->getString("_id").get();
//        cout << "Looking for: " << *id << endl;
//        cout << "Found        " << *id2 << endl;
        if ((id2 == NULL) || (id2->compare(*id) != 0)) {
            if (id2 != NULL) {
                cout << "Looking for: " << *id << " and got " << *id2 << endl;
            }
            cout << "Error " << endl;
        }
    }

    clock_gettime(interval, &ts2);

    #ifdef LINUX
    timespec etime = diff(ts1, ts2);
    double secs = etime.tv_sec + ((double)etime.tv_nsec / 1000000000.0);
    #else
    struct timeval etime = diff(ts1, ts2);
    double secs = etime.tv_sec + ((double)etime.tv_usec / 1000000.0);
    #endif

    cout<< "finds " << __ids.size() << ", secs: " << secs << endl;

    cout << "Throughput: " << (__ids.size() / secs) << " ops." << endl;
    cout << "------------------------------------------------------------" << endl;
}

void testFindPrevious() {
   int interval;
    #ifdef LINUX
    timespec ts1;
    timespec ts2;
    interval = CLOCK_REALTIME; //CLOCK_PROCESS_CPUTIME_ID;
    #endif
    #ifdef WINDOWS
    struct timeval ts1;
    struct timeval ts2;
    interval = 0;
    #endif

    FileInputStream fis("temp.txt", "rb");
    std::vector<std::string*> ids;
    while (!fis.eof()) {
        ids.push_back(fis.readString().get());
    }
    fis.close();

    clock_gettime(interval, &ts1);

    for (std::vector<string*>::iterator i = ids.begin(); i != ids.end(); i++) {
        boost::shared_ptr<string> id(*i);

        boost::shared_ptr<BSONObj> obj(new BSONObj());
        obj->add("_id", id);
        boost::shared_ptr<BSONObj> res = controller.findFirst("sp1.customer", obj);
        std::string* id2 = res->getString("_id").get();
//        cout << "Looking for: " << *id << endl;
//        cout << "Found        " << *id2 << endl;
        if ((id2 == NULL) || (id2->compare(*id) != 0)) {
            if (id2 != NULL) {
                cout << "Looking for: " << *id << " and got " << *id2 << endl;
            }
            cout << "Error " << endl;
        }
    }

    clock_gettime(interval, &ts2);

    #ifdef LINUX
    timespec etime = diff(ts1, ts2);
    double secs = etime.tv_sec + ((double)etime.tv_nsec / 1000000000.0);
    #else
    struct timeval etime = diff(ts1, ts2);
    double secs = etime.tv_sec + ((double)etime.tv_usec / 1000000.0);
    #endif

    cout<< "finds " << ids.size() << ", secs: " << secs << endl;

    cout << "Throughput: " << (ids.size() / secs) << " ops." << endl;
    cout << "------------------------------------------------------------" << endl;
}

int main(int argc, char* args[])
{
    if (argc < 2) {
        cout << "Usage: " << endl;
        cout << "    test-db inserts" << endl << endl;
        cout << "inserts:   number of inserts to execute" << endl << endl;
        return 0;
    }
    controller.initialize();

    testFindPrevious();
    int x = atoi(args[1]);
    testMassiveInsert(x);
    testFinds();

    controller.shutdown();
    return 0;
}
