package com.sinco.bpm.workflow;

import com.sinco.bpm.data.entities.MasterEntity;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.persistence.Entity;
import com.sinco.persistence.EntityManager;
import com.sinco.persistence.EntityManagerFactory;
import com.sinco.persistence.Id;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

@Entity
public class ProcessInstance implements java.io.Serializable {

    public ProcessInstance() {
    }
    
    private int id;

    private ProcessDefinition processDefinition;

    private InstanceStatus status;

    private Vector assignments;

    private Vector propertyValues;
    
    private List<Token> currentTokens = new ArrayList<Token>();
    
    private MasterEntity masterEntity;

    public void addCurrentToken(Token token) {
        if (!getCurrentTokens().contains(token)) {
            getCurrentTokens().add(token);
        }
    }

    public void addCurrentToken(List<Token> token) {
        // TODO Test if the token is already in the list
        getCurrentTokens().addAll(token);
    }

    @Id
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public ProcessDefinition getProcessDefinition() {
        return processDefinition;
    }

    public void setProcessDefinition(ProcessDefinition processDefinition) {
        this.processDefinition = processDefinition;
    }

    public InstanceStatus getStatus() {
        return status;
    }

    public void setStatus(InstanceStatus status) {
        this.status = status;
    }

    public Vector getAssignments() {
        return assignments;
    }

    public void setAssignments(Vector assignments) {
        this.assignments = assignments;
    }

    public Vector getPropertyValues() {
        return propertyValues;
    }

    public void setPropertyValues(Vector propertyValues) {
        this.propertyValues = propertyValues;
    }

    public List<Token> getCurrentTokens() {
        return currentTokens;
    }

    public MasterEntity getMasterEntity() {
        return masterEntity;
    }

    public void setMasterEntity(MasterEntity masterEntity) {
        this.masterEntity = masterEntity;
    }
    
}
