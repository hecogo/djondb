package com.sinco.bpm.workflow.metadata;

@com.sinco.persistence.Entity
public class StartEvent extends CommonEvent implements java.io.Serializable {

    public StartEvent() {
        setEventType(EventType.START);
    }
    
    private Trigger startTrigger;
    
    public Trigger getStartTrigger() {
        return startTrigger;
    }

    public void setStartTrigger(Trigger startTrigger) {
        this.startTrigger = startTrigger;
    }
}