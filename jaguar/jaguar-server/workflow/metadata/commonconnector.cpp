#include "commonconnector.h"
#include "util.h"

CommonConector::CommonConector() {
    Logger* log = getLogger(NULL);
    if (log->isDebug()) log->debug("CommonConector()");
    taskSource = NULL;
    eventSource = NULL;
    eventTarget = NULL;
    delete(log);
}

CommonConector::~CommonConector() {
    Logger* log = getLogger(NULL);
    if (log->isDebug()) log->debug("~CommonConector()");
    delete(log);
}


