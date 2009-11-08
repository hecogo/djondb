/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.metadata.deployment;

import com.sinco.bpm.workflow.metadata.CommonConector;
import com.sinco.bpm.workflow.metadata.CommonEvent;
import com.sinco.bpm.workflow.metadata.EndEvent;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.StartEvent;
import java.util.ArrayList;
import java.util.Collection;

/**
 *
 * @author cross
 */
public class Event {
    private int id;
    private String name;
    private String type;
    private Collection<SequenceFlow> sequenceFlows = new ArrayList<SequenceFlow>();

    public Event() {
        System.out.println("a");
    }
    
    public int getId() {
        return id;
    }

    public void setId(int id) {
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

    public CommonEvent getEventDef(Process process, ProcessDefinition def) {
        CommonEvent res = null;
        if (getType().equals("start")) {
            res = new StartEvent();
        } else if (getType().equals("end")) {
            res = new EndEvent();
        } else {
            throw new IllegalArgumentException("Type " + getType() + " not supported.");
        }
        res.setId(getId());
        res.setProcessDefinition(def);
        ArrayList<CommonConector> newFlows = new ArrayList<CommonConector>();
        for (SequenceFlow flow : getSequenceFlows()) {
            newFlows.addAll(flow.getSequenceFlowDef(process, def, res));
        }
        res.setSequenceFlows(newFlows);
        return res;
    }
    
}
