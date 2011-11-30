#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <string>
#include "../defs.h"
#include "dtime.h"
#include <ctime>
#ifndef WINDOWS
#include <time.h>
#endif
#ifdef WINDOWS
#include <Windows.h>
#endif

using namespace std;

class Logger {
    private:
        bool m_debug;
        bool m_info;
        bool m_warn;
        void* m_clazz;

        int _interval;
        #ifdef LINUX
        timespec _ts1;
        timespec _ts2;
        #endif
        #ifdef WINDOWS
        struct timeval _ts1;
        struct timeval _ts2;
        #endif


    public:
        Logger(void* clazz);
        bool isDebug();
        bool isInfo();
        bool isWarn();
        void debug(string message, ...);
        void error(string error, ...);
        void error(exception ex);
        void info(string message, ...);
        void warn(string warn, ...);

        void startTimeRecord();
        void stopTimeRecord();

        DTime recordedTime();
};

Logger* getLogger(void* clazz);

#endif
