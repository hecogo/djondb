
#include <iostream>
#include <stdio.h>
#include "util.h"
#include "networkservice.h"
#include "net/defs.h"

using namespace std;

int main() {
    Logger* log = getLogger(NULL);
    try {
        TimeRecord* record = getTimeRecord();

        NetworkService service;
        service.start();
        log->info("Server started up: " + toString((float) record->getTimeInMillis()));

        cout << "Press any key to stop it" << endl;

        getchar();

        delete(record);
        service.stop();
    } catch (NetworkException e) {
        log->error(e);
    }
    log->info("before delete log");
    delete(log);
    return 0;
}
