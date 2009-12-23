#ifndef COMMONEVENT_H_INCLUDED
#define COMMONEVENT_H_INCLUDED

#include <vector>

#include "defs.h"
#include "connectorsourceable.h"
#include "connectortargetable.h"
#include "commonconnector.h"

class Assignment;
class Pool;
class ProcessDefinition;

class CommonEvent : public ConnectorSourceable , public ConnectorTargetable {
private:
    vector<CommonConector*>* sequenceFlows;
    long id;
    EventType eventType;
    vector<Assignment*>* assigments;
    Pool* pool;
    ProcessDefinition* processDefinition;

public:
    CommonEvent() {
        sequenceFlows = new vector<CommonConector*>();
        assigments = new vector<Assignment*>();
    }

    virtual ~CommonEvent() {
        if (sequenceFlows) {
            for (vector<CommonConector*>::iterator iter = sequenceFlows->begin(); iter != sequenceFlows->end(); iter++) {
                CommonConector* connector = *iter;
                delete(connector);
            }
            delete(sequenceFlows);
        }
        delete(assigments);
    }
    
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    EventType getEventType() {
        return eventType;
    }

    void setEventType(EventType _eventType) {
        eventType = _eventType;
    }

    Pool* getPool() {
        return pool;
    }

    void setPool(Pool* _pool) {
        pool = _pool;
    }

    vector<CommonConector*>* getSequenceFlows() {
        return sequenceFlows;
    }

    void setSequenceFlows(vector<CommonConector*>* _sequenceFlows) {
        sequenceFlows = _sequenceFlows;
    }

    vector<Assignment*>* getAssigments() {
        return assigments;
    }

    void setAssigments(vector<Assignment*>* _assigments) {
        assigments = _assigments;
    }

    ProcessDefinition* getProcessDefinition() {
        return processDefinition;
    }

    void setProcessDefinition(ProcessDefinition* _processDefinition) {
        processDefinition = _processDefinition;
    }
};



#endif // COMMONEVENT_H_INCLUDED
