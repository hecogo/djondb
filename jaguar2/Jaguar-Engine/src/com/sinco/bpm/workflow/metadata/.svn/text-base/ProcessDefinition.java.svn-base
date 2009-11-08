package com.sinco.bpm.workflow.metadata;

import com.sinco.persistence.Id;
import java.util.List;

@com.sinco.persistence.Entity
public class ProcessDefinition implements java.io.Serializable {
    public static final long serialVersionUID = 1L;
    
    private long id;
    
    private String definitionName;
    
    private ProcessType processType;
    
    private List<Property> properties;
    
    private List<CommonEvent> events;

    private List<Pool> pools;
    
    private List<ActivityCommon> tasks;

    private String masterEntity;
    
    public ProcessType getProcessType() {
        return processType;
    }

    public void setProcessType(ProcessType processType) {
        this.processType = processType;
    }

    public List<Property> getProperties() {
        return properties;
    }

    public void setProperties(List<Property> properties) {
        this.properties = properties;
    }

    public List<Pool> getPools() {
        return pools;
    }

    public void setPools(List<Pool> pools) {
        this.pools = pools;
    }

    public String getDefinitionName() {
        return definitionName;
    }

    public void setDefinitionName(String definitionName) {
        this.definitionName = definitionName;
    }

    public List<ActivityCommon> getTasks() {
        return tasks;
    }

    public void setTasks(List<ActivityCommon> tasks) {
        this.tasks = tasks;
    }
    
    @Id
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public List<CommonEvent> getEvents() {
        return events;
    }

    public void setEvents(List<CommonEvent> events) {
        this.events = events;
    }

    public String getMasterEntity() {
        return masterEntity;
    }

    public void setMasterEntity(String masterEntity) {
        this.masterEntity = masterEntity;
    }
    
}