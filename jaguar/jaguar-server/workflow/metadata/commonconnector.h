#ifndef COMMONCONNECTOR_H_INCLUDED
#define COMMONCONNECTOR_H_INCLUDED

class Task;
class CommonEvent;

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
        sourceType = TASK;
    }

    Task* getTaskTarget() {
        return taskTarget;
    }

    void setTaskTarget(Task* _taskTarget) {
        taskTarget = _taskTarget;
        targetType = TASK;
    }

    CommonEvent* getEventSource() {
        return eventSource;
    }

    void setEventSource(CommonEvent* _eventSource) {
        eventSource = _eventSource;
        sourceType = EVENT;
    }

    CommonEvent* getEventTarget() {
        return eventTarget;
    }

    void setEventTarget(CommonEvent* _eventTarget) {
        eventTarget = _eventTarget;
        targetType = EVENT;
    }

    ConnectorType getSourceType() {
        return sourceType;
    }

    ConnectorType getTargetType() {
        return targetType;
    }
};


#endif // COMMONCONNECTOR_H_INCLUDED
