/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.metadata.deployment;

import com.sinco.bpm.workflow.metadata.ActivityCommon;
import com.sinco.bpm.workflow.metadata.ActivityStatus;
import com.sinco.bpm.workflow.metadata.ActivityType;
import com.sinco.bpm.workflow.metadata.CommonConector;
import com.sinco.bpm.workflow.metadata.ManualTask;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.ServiceTask;
import com.sinco.bpm.workflow.metadata.TaskType;
import java.util.ArrayList;
import java.util.Collection;

/**
 *
 * @author cross
 */
public class Task {

    private long id;
    private String name;
    private String type;
    private int form;
    private Collection<SequenceFlow> sequenceFlows = new ArrayList<SequenceFlow>();

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void addSequenceFlow(SequenceFlow flow) {
        sequenceFlows.add(flow);
    }

    public Collection<SequenceFlow> getSequenceFlows() {
        return sequenceFlows;
    }

    public void setSequenceFlows(Collection<SequenceFlow> sequenceFlows) {
        this.sequenceFlows = sequenceFlows;
    }

    public com.sinco.bpm.workflow.metadata.Task getTaskDefinition(Process process, ProcessDefinition def) {
        com.sinco.bpm.workflow.metadata.Task newTask = null;
        if (getType().equals("manual")) {
            newTask = new ManualTask();
            newTask.setTaskType(TaskType.MANUAL);
        } else if (getType().equals("service")) {
            newTask = new ServiceTask();
            newTask.setTaskType(TaskType.SERVICE);
        } else {
            throw new IllegalArgumentException("Type " + getType() + " not supported");
        }
        newTask.setId(getId());
        newTask.setTaskName(getName());
        newTask.setActivityType(ActivityType.TASK);
        newTask.setStatus(ActivityStatus.NONE);

        ArrayList<CommonConector> newFlows = new ArrayList<CommonConector>();
        for (SequenceFlow flow : getSequenceFlows()) {
            newFlows.addAll(flow.getSequenceFlowDef(process, def, newTask));
        }
        newTask.setSequenceFlows(newFlows);
        return newTask;
    }

    public int getForm() {
        return form;
    }

    public void setForm(int form) {
        this.form = form;
    }
}
