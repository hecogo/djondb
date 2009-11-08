#include <ctime>
#include "util.h"

using namespace std;

TimeRecord::TimeRecord() {
    start = time(NULL);
}

int TimeRecord::getTimeInMillis() {
    time_t end = time(NULL);

    return end - start;
}

TimeRecord* getTimeRecord() {
    TimeRecord* record = new TimeRecord();
    return record;
}

