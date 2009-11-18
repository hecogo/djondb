#ifndef STARTEVENT_H_INCLUDED
#define STARTEVENT_H_INCLUDED

class StartEvent : public CommonEvent {
private:
    Trigger* startTrigger;
public:
    StartEvent() {};
    Trigger* getStartTrigger() {
        return startTrigger;
    }

    void setStartTrigger(Trigger* _startTrigger) {
        startTrigger = _startTrigger;
    }
};

#endif // STARTEVENT_H_INCLUDED
