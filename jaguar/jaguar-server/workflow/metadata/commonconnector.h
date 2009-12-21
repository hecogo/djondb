#ifndef COMMONCONNECTOR_H_INCLUDED
#define COMMONCONNECTOR_H_INCLUDED

#include "defs.h"
#include <string>

class Task;
class CommonEvent;

using namespace std;

class CommonConector {
private:
    long id;
    string* connectorName;
    Task* taskSource;
    Task* taskTarget;
    CommonEvent* eventSource;
    CommonEvent* eventTarget;
    ConnectorType sourceType;
    ConnectorType targetType;

public:
    ~CommonConector() {
        delete(connectorName);
    }
    
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getConnectorName() {
        return connectorName;
    }

    void setConnectorName(string* _connectorName) {
        connectorName = _connectorName;
    }

    Task* getTaskSource() {
        return taskSource;
    }

    void setTaskSource(Task* _taskSource) {
        taskSource = _taskSource;
        sourceType = TASK_CTTYPE;
    }

    Task* getTaskTarget() {
        return taskTarget;
    }

    void setTaskTarget(Task* _taskTarget) {
        taskTarget = _taskTarget;
        targetType = TASK_CTTYPE;
    }

    CommonEvent* getEventSource() {
        return eventSource;
    }

    void setEventSource(CommonEvent* _eventSource) {
        eventSource = _eventSource;
        sourceType = EVENT_CTTYPE;
    }

    CommonEvent* getEventTarget() {
        return eventTarget;
    }

    void setEventTarget(CommonEvent* _eventTarget) {
        eventTarget = _eventTarget;
        targetType = EVENT_CTTYPE;
    }

    ConnectorType getSourceType() {
        return sourceType;
    }

    ConnectorType getTargetType() {
        return targetType;
    }
};


#endif // COMMONCONNECTOR_H_INCLUDED
