#include "../jaguar-server-lib/util/timerecord.h"
#include "../jaguar-server-lib/util/logger/logger.h"
//#include "../jaguar-server-lib/util/util.h"
#include <pthread.h>
#include "util.h"
#include <string>

using namespace std;

int main() {
    Logger* log = getLogger(typeid (TimeRecord));
    TimeRecord* record = getTimeRecord();

    int i = 1;
    string s = to_string(i);
    log->info("Server started up: " + s);

    return 0;
}

