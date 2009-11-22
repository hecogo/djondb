#ifndef TIMERECORD_H_INCLUDED
#define TIMERECORD_H_INCLUDED

#include <ctime>

using namespace std;

class TimeRecord
{
public:
    time_t start;

    TimeRecord();

    int getTimeInMillis();
};

TimeRecord* getTimeRecord();

#endif
