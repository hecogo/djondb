package com.sinco.bpm.workflow.metadata;

import com.sinco.persistence.Id;


public abstract class CommonConector implements java.io.Serializable {
    
    private long id;
    
    private String connectorName;
    
    private Task taskSource;
    
    private Task taskTarget;

    private CommonEvent eventSource;
    
    private CommonEvent eventTarget;

    @Id
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getConnectorName() {
        return connectorName;
    }

    public void setConnectorName(String connectorName) {
        this.connectorName = connectorName;
    }

    protected Task getTaskSource() {
        return taskSource;
    }

    protected void setTaskSource(Task taskSource) {
        this.taskSource = taskSource;
    }

    protected Task getTaskTarget() {
        return taskTarget;
    }

    protected void setTaskTarget(Task taskTarget) {
        this.taskTarget = taskTarget;
    }

    protected CommonEvent getEventSource() {
        return eventSource;
    }

    protected void setEventSource(CommonEvent eventSource) {
        this.eventSource = eventSource;
    }

    protected CommonEvent getEventTarget() {
        return eventTarget;
    }

    protected void setEventTarget(CommonEvent eventTarget) {
        this.eventTarget = eventTarget;
    }

    public ConnectorSourceable getSource() {
        if (taskSource != null) {
            return taskSource;
        } else {
            return eventSource;
        }
    }

    public void setSource(ConnectorSourceable source) {
        if (source instanceof Task) {
            setTaskSource((Task)source);
            setEventSource(null);
        } else {
            setTaskSource(null);
            setEventSource((CommonEvent)source);
        }
    }

    public ConnectorTargetable getTarget() {
        if (taskTarget != null) {
            return taskTarget;
        } else {
            return eventTarget;
        }
    }

    public void setTarget(ConnectorTargetable target) {
        if (target instanceof Task) {
            setTaskTarget((Task)target);
            setEventTarget(null);
        } else {
            setTaskTarget(null);
            setEventTarget((CommonEvent)target);
        }
    }
}