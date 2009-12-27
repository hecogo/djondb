#ifndef COMMONEVENT_H_INCLUDED
#define COMMONEVENT_H_INCLUDED

#include <vector>

#include "defs.h"
#include "connectorsourceable.h"
#include "connectortargetable.h"
#include "commonconnector.h"

class Assignment;

class CommonEvent : public ConnectorSourceable , public ConnectorTargetable {
private:
    vector<CommonConector*> sequenceFlows;
    long id;
    EventType eventType;
    vector<Assignment*> assigments;

public:
    CommonEvent() {
    }

    virtual ~CommonEvent() {
        for (vector<CommonConector*>::iterator iter = sequenceFlows.begin(); iter != sequenceFlows.end(); iter++) {
            CommonConector* connector = *iter;
            delete(connector);
        }
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

    vector<CommonConector*> getSequenceFlows() {
        return sequenceFlows;
    }

    void setSequenceFlows(vector<CommonConector*> _sequenceFlows) {
        sequenceFlows = _sequenceFlows;
    }

    vector<Assignment*> getAssigments() {
        return assigments;
    }

    void setAssigments(vector<Assignment*> _assigments) {
        assigments = _assigments;
    }
};



#endif // COMMONEVENT_H_INCLUDED
