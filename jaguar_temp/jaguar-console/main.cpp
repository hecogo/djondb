#include <iostream>
#include "../jaguar-server-lib/util/timerecord.h"
#include "../jaguar-server-lib/util/logger/logger.h"
#include <pthread.h>
#include <cstdio>
#include <sstream>
#include "../jaguar-server-lib/util/util.h"

using namespace std;

int main()
{
    Logger* log = getLogger(NULL);
    TimeRecord* record = getTimeRecord();


    log->info("Server started up: " + toString(record->getTimeInMillis()));
    return 0;
}
