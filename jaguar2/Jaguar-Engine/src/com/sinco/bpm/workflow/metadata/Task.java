package com.sinco.bpm.workflow.metadata;

import java.util.List;

public abstract class Task extends ActivityCommon implements java.io.Serializable, ConnectorSourceable, ConnectorTargetable {

    private List<CommonConector> sequenceFlows;

    private TaskType taskType;
    
    private String taskName;
    
    public TaskType getTaskType() {
        return taskType;
    }

    public void setTaskType(TaskType taskType) {
        this.taskType = taskType;
    }

    public List<CommonConector> getSequenceFlows() {
        return sequenceFlows;
    }

    public void setSequenceFlows(List<CommonConector> sequenceFlows) {
        this.sequenceFlows = sequenceFlows;
    }

    public String getTaskName() {
        return taskName;
    }

    public void setTaskName(String taskName) {
        this.taskName = taskName;
    }

}