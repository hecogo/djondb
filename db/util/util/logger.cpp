#include "logger.h"
#include "stringfunctions.h"

#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#define PRINT(TYPE, CLAZZ) \
  char* buffer = (char*)malloc(1000); \
  memset(buffer, 0, 1000); \
  va_list args; \
  va_start (args, message); \
  vsprintf (buffer, message.c_str(), args); \
  va_end(args); \
  std::string result; \
  std::stringstream ss; \
  ss << buffer; \
  result = ss.str(); \
  free(buffer); \
  cout << TYPE << ": " << CLAZZ << ": " << result << endl;



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
		temp.tv_usec = 1000000000+end.tv_usec-start.tv_usec;
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

Logger* getLogger(void* clazz) {
    Logger* logger = new Logger(clazz);

    return logger;
}

Logger::Logger(void* clazz) {
    m_clazz = clazz;
    m_debug = true;
    m_info = true;
    m_warn = true;
}

/*
std::string format(const char * message, ...) {
  char* buffer = (char*)malloc(1000);
  memset(buffer, 0, 1000);
  va_list args;
  va_start (args, message);
  vsprintf (buffer,message, args);
  va_end(args);
  std::string result;
  std::stringstream ss;
  ss << buffer;
  result = ss.str();
  free(buffer);
}
*/

void Logger::debug(string message, ...) {
    PRINT("DEBUG", m_clazz);
}

void Logger::info(string message, ...) {
    PRINT("INFO", m_clazz);
}


void Logger::warn(string message, ...) {
    PRINT("WARN", m_clazz);
}


void Logger::error(string message, ...) {
    PRINT("ERROR", m_clazz);
}

void Logger::error(exception ex) {
    cout << m_clazz << ":" << ex.what() << endl;
}

bool Logger::isDebug() {
    return m_debug;
}

bool Logger::isInfo() {
    return m_info;
}

bool Logger::isWarn() {
    return m_warn;
}

void Logger::startTimeRecord() {
    int interval = CLOCK_REALTIME;// CLOCK_PROCESS_CPUTIME_ID;

    clock_gettime(interval, &_ts1);
}

void Logger::stopTimeRecord() {
    int interval = CLOCK_REALTIME;// CLOCK_PROCESS_CPUTIME_ID;
    clock_gettime(interval, &_ts2);
}

DTime Logger::recordedTime() {
    #ifdef LINUX
    timespec etime = diff(_ts1, _ts2);
    double secs = etime.tv_sec + ((double)etime.tv_nsec / 1000000000.0);
    #else
    struct timeval etime = diff(_ts1, _ts2);
    double secs = etime.tv_sec + ((double)etime.tv_usec / 1000000.0);
    #endif

    DTime result(secs);

    return result;
}
