/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import com.sinco.bpm.workflow.metadata.TaskType;
import java.io.Serializable;

/**
 *
 * @author JuanC
 */
public class TaskVO implements Serializable {
    private long id;
    private String taskName;
    private TaskType taskType;
    private int form;

    public String getTaskName() {
        return taskName;
    }

    public void setTaskName(String taskName) {
        this.taskName = taskName;
    }
    
    @Override
    public String toString() {
        return "Task [taskName=" + getTaskName() + "]";
    }

    public TaskType getTaskType() {
        return taskType;
    }

    public void setTaskType(TaskType taskType) {
        this.taskType = taskType;
    }

    void setId(long id) {
        this.id = id;
    }

    public long getId() {
        return id;
    }

    public int getForm() {
        return form;
    }

    public void setForm(int form) {
        this.form = form;
    }

}
