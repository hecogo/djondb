#include "service.h"
#include "networkservice.h"
#include <stdlib.h>

NetworkService* __service;

int service_restart() {
}

int service_startup() {
    if (__service != NULL) {
        __service->stop();
    }
    __service = new NetworkService();
    __service->start();
}

int service_shutdown() {
}

int service_status() {
}
