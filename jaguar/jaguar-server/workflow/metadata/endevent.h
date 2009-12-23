#ifndef ENDEVENT_H_INCLUDED
#define ENDEVENT_H_INCLUDED

#include "commonevent.h"


class EndEvent : public CommonEvent {
public:
    EndEvent() {
        setEventType(END_EVENTTYPE);
    }

    virtual ~EndEvent() {
    }
};


#endif // ENDEVENT_H_INCLUDED
