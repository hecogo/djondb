#include "service.h"
#include "networkservice.h"



int service_restart() {
}

int service_startup() {
    NetworkService* service;
//    if (service != NULL) {
//        service->stop();
//    }
    service = new NetworkService();
    service->start();
}

int service_shutdown() {
}

int service_status() {
}
