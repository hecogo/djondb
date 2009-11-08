/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import java.io.Serializable;

/**
 *
 * @author JuanC
 */
public class TokenVO implements Serializable {
    private long id;
    private TaskVO task;
    private ProcessInstanceVO processInstance;
    private TokenStatus status;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public TaskVO getTask() {
        return task;
    }

    public void setTask(TaskVO task) {
        this.task = task;
    }

    public ProcessInstanceVO getProcessInstance() {
        return processInstance;
    }

    public void setProcessInstance(ProcessInstanceVO processInstance) {
        this.processInstance = processInstance;
    }

    public TokenStatus getStatus() {
        return status;
    }

    public void setStatus(TokenStatus status) {
        this.status = status;
    }
    
    @Override
    public String toString() {
        return "Token [id=" + getId() + ",status=" + getStatus().toString() + ",ProcessInstance=" + getProcessInstance().toString() + ",task=" + getTask().getTaskName() + "]";
    }
}