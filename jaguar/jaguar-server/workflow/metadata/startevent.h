#ifndef STARTEVENT_H_INCLUDED
#define STARTEVENT_H_INCLUDED

#include "commonevent.h"


class StartEvent : public CommonEvent {
private:
    Trigger* startTrigger;
public:
    StartEvent() {
        setEventType(START_EVENTTYPE);
        startTrigger = NULL;
    };

    virtual ~StartEvent() {
        if (startTrigger) {
            delete(startTrigger);
        }
    }

    Trigger* getStartTrigger() {
        return startTrigger;
    }

    void setStartTrigger(Trigger* _startTrigger) {
        startTrigger = _startTrigger;
    }
};

#endif // STARTEVENT_H_INCLUDED
