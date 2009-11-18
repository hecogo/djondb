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
    }

    Task* getTaskTarget() {
        return taskTarget;
    }

    void setTaskTarget(Task* _taskTarget) {
        taskTarget = _taskTarget;
    }

    CommonEvent* getEventSource() {
        return eventSource;
    }

    void setEventSource(CommonEvent* _eventSource) {
        eventSource = _eventSource;
    }

    CommonEvent* getEventTarget() {
        return eventTarget;
    }

    void setEventTarget(CommonEvent* _eventTarget) {
        eventTarget = _eventTarget;
    }
};


#endif // COMMONCONNECTOR_H_INCLUDED
