/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.metadata.deployment;

import com.sinco.bpm.workflow.metadata.ConnectorSourceable;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import java.util.ArrayList;
import java.util.Collection;

/**
 *
 * @author cross
 */
public class SequenceFlow {

    private int id;
    private Collection<Target> targets = new ArrayList<Target>();

    public SequenceFlow() {
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void addTarget(Target target) {
        targets.add(target);
    }

    public Collection<Target> getTargets() {
        return targets;
    }

    public void setTargets(Collection<Target> targets) {
        this.targets = targets;
    }

    public Collection<com.sinco.bpm.workflow.metadata.SequenceFlow> getSequenceFlowDef(Process process, ProcessDefinition def, ConnectorSourceable source) {
        ArrayList<com.sinco.bpm.workflow.metadata.SequenceFlow> res = new ArrayList<com.sinco.bpm.workflow.metadata.SequenceFlow>();
        for (Target target : getTargets()) {
            com.sinco.bpm.workflow.metadata.SequenceFlow newFlow = new com.sinco.bpm.workflow.metadata.SequenceFlow();
            newFlow.setSource(source);
            if (target.getTaskId() != 0) {
                Task task = process.getTask(target.getTaskId());
                newFlow.setTarget(task.getTaskDefinition(process, def));
            } else if (target.getEventId() != 0) {
                Event evt = process.getEvents(target.getEventId());
                newFlow.setTarget(evt.getEventDef(process, def));
            }
            newFlow.setQuantity(1);
            res.add(newFlow);
        }
        return res;
    }
}
