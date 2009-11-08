package com.sinco.bpm.workflow.metadata;

import com.sinco.persistence.Id;
import java.util.List;

//    @NamedQuery(name="findByProcessDefinitionEventType", query="select object(o) from CommonEvent as o where o.eventType = :eventType and o.processDefinition = :processDefinition")
public abstract class CommonEvent implements java.io.Serializable, ConnectorSourceable, ConnectorTargetable {
    
    private List<CommonConector> sequenceFlows;
    
    private long id;
    
    private EventType eventType;
    
    private List<Assignment> assigments;
    
    private Pool pool;
    
    private ProcessDefinition processDefinition;
    
    @Id
    public long getId() {
        return id;
    }
    
    public void setId(long id) {
        this.id = id;
    }
    
    public EventType getEventType() {
        return eventType;
    }
    
    public void setEventType(EventType eventType) {
        this.eventType = eventType;
    }
    
    public Pool getPool() {
        return pool;
    }
    
    public void setPool(Pool pool) {
        this.pool = pool;
    }
    
    public List<CommonConector> getSequenceFlows() {
        return sequenceFlows;
    }
    
    public void setSequenceFlows(List<CommonConector> sequenceFlows) {
        this.sequenceFlows = sequenceFlows;
    }
    
    public List<Assignment> getAssigments() {
        return assigments;
    }
    
    public void setAssigments(List<Assignment> assigments) {
        this.assigments = assigments;
    }
    
    public ProcessDefinition getProcessDefinition() {
        return processDefinition;
    }
    
    public void setProcessDefinition(ProcessDefinition processDefinition) {
        this.processDefinition = processDefinition;
    }
    
}