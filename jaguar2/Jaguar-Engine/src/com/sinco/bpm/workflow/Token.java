package com.sinco.bpm.workflow;

import com.sinco.bpm.workflow.metadata.Task;
import com.sinco.persistence.Entity;
import com.sinco.persistence.Id;

@Entity
public class Token implements java.io.Serializable {

    private long id;
    
    private Task task;
    
    private ProcessInstance processInstance;
    
    private TokenStatus status;

    @Id
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Task getTask() {
        return task;
    }

    public void setTask(Task task) {
        this.task = task;
    }

    public ProcessInstance getProcessInstance() {
        return processInstance;
    }

    public void setProcessInstance(ProcessInstance processInstance) {
        this.processInstance = processInstance;
    }

    public TokenStatus getStatus() {
        return status;
    }

    public void setStatus(TokenStatus status) {
        this.status = status;
    }
}