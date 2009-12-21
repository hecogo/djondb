
#include <iostream>
#include <stdio.h>
#include "util.h"
#include "networkservice.h"

using namespace std;

int main() {
    Logger* log = getLogger(NULL);
    TimeRecord* record = NULL;
    NetworkService* service = NULL;
    try {
        record = getTimeRecord();

        service = new NetworkService();
        service->start();
        log->info("Server started up: " + toString((float)record->getTimeInMillis()));

        cout << "Press any key to stop it" << endl;

        getchar();

        service->stop();
    } catch (NetworkException e) {
        log->error(e);
    }
    delete(service);
    delete(record);
    delete(log);
    return 0;
}