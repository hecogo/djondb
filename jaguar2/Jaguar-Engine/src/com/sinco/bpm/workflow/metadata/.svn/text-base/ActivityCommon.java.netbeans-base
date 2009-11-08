package com.sinco.bpm.workflow.metadata;

import com.sinco.persistence.Id;

/**
 *
 * Contains common properties for Tasks and subprocess
 *
 **/
public abstract class ActivityCommon implements java.io.Serializable {
    
    private long id;
    
    private ActivityType activityType;
    
    private ActivityStatus status;
    
    /**
     *  Number of tokens required to start the activity
     */
    private int startQuantity = 1;
    
    private LoopType loopType;
    
    private ProcessDefinition processDefinition;

    @Id
    public long getId() {
        return id;
    }
    
    public void setId(long id) {
        this.id = id;
    }
    
    public ActivityType getActivityType() {
        return activityType;
    }
    
    public void setActivityType(ActivityType activityType) {
        this.activityType = activityType;
    }
    
    public ActivityStatus getStatus() {
        return status;
    }
    
    public void setStatus(ActivityStatus status) {
        this.status = status;
    }
    
    public int getStartQuantity() {
        return startQuantity;
    }
    
    public void setStartQuantity(int startQuantity) {
        this.startQuantity = startQuantity;
    }
    
    public LoopType getLoopType() {
        return loopType;
    }
    
    public void setLoopType(LoopType loopType) {
        this.loopType = loopType;
    }
    
    public ProcessDefinition getProcessDefinition() {
        return processDefinition;
    }
    
    public void setProcessDefinition(ProcessDefinition processDefinition) {
        this.processDefinition = processDefinition;
    }
    
}