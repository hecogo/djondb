package com.sinco.bpm.workflow;

import com.sinco.bpm.data.entities.MasterEntity;
import com.sinco.bpm.workflow.metadata.CommonConector;
import com.sinco.bpm.workflow.metadata.CommonEvent;
import com.sinco.bpm.workflow.metadata.ConnectorTargetable;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.ProcessDefinitionFacade;
import com.sinco.bpm.workflow.metadata.StartEvent;
import com.sinco.bpm.workflow.metadata.Task;
import com.sinco.persistence.EntityManager;
import com.sinco.persistence.EntityManagerFactory;
import com.sinco.persistence.EntityManagerType;
import com.sinco.persistence.EntityNotFoundException;
import java.util.ArrayList;
import java.util.List;

public class WorkflowFacade  {
    private EntityManager entityManager;
    
    public WorkflowFacade() {
        entityManager = EntityManagerFactory.getEntityManager(EntityManagerType.METADATA);
    }
    
    public ProcessInstance createProcessInstance(long definition) throws EntityNotFoundException {
        ProcessDefinitionFacade processDefinitionFacade = new ProcessDefinitionFacade();
        ProcessDefinition def = processDefinitionFacade.find(definition);

        return createProcessInstance(def);
    }

    public ProcessInstance createProcessInstance(ProcessDefinition def) {
        ProcessInstance processInstance = new ProcessInstance();
        processInstance.setProcessDefinition(def);
        MasterEntity master = getMasterEntity(def);
        processInstance.setMasterEntity(master);
        List<StartEvent> startEvents = getStartEvents(def);
        for (StartEvent evt : startEvents) {
            processInstance = processEvent(processInstance, evt);
        }
        processInstance = (ProcessInstance) persist(processInstance);

        return processInstance;
    }

    private MasterEntity getMasterEntity(ProcessDefinition def) {
        try {
            if (def.getMasterEntity() != null) {
                @SuppressWarnings("unchecked")
                Class<MasterEntity> clazz = (Class<MasterEntity>) Class.forName("com.sinco.bpm.data.entities." + def.getMasterEntity());
                MasterEntity master = clazz.newInstance();
                return master;
            } else {
                return null;
            }
        } catch (InstantiationException ex) {
            throw new RuntimeException(ex);
        } catch (IllegalAccessException ex) {
            throw new RuntimeException(ex);
        } catch (ClassNotFoundException ex) {
            throw new RuntimeException(ex);
        }
    }

    private List<StartEvent> getStartEvents(ProcessDefinition def) {
        List<CommonEvent> commonEvents = def.getEvents();
        ArrayList<StartEvent> startEvents = new ArrayList<StartEvent>();
        for (CommonEvent com : commonEvents) {
            if (com instanceof StartEvent) {
                startEvents.add((StartEvent) com);
            }
        }
        // If the process definition does not contain start events the workflow 
        // will create a virtual StartEvent with the tasks with no incoming 
        // flow
        if (startEvents.size() == 0) {
            throw new UnsupportedOperationException("Not implemented yet");
        }
        return startEvents;
    }

    private Object persist(Object obj) {
        entityManager.persist(obj);
        return obj;
    }

    public ProcessInstance processEvent(ProcessInstance processInstance, StartEvent evt) {
        // Every new process generates a new tokens
        List<CommonConector> sequenceFlows = evt.getSequenceFlows();
        TokenFacade tokenFacade = new TokenFacade();
        for (CommonConector connector : sequenceFlows) {
            ConnectorTargetable target = connector.getTarget();
            if (target instanceof Task) {
                Token token = new Token();
                Task task = (Task) target;
                token.setTask(task);
                token.setProcessInstance(processInstance);
                token.setStatus(TokenStatus.NONE);
                List<Token> newTokens = tokenFacade.processToken(processInstance, token);
                if (newTokens != null) {
                    processInstance.addCurrentToken(newTokens);
                }
            }
        }

        return processInstance;
    }

    public List<Token> processToken(ProcessInstance instance, TokenVO tokenVO) {
        try {
            TokenFacade tokenFacade = new TokenFacade();
            Token token = tokenFacade.findBy(tokenVO);
            return tokenFacade.processToken(instance, token);
        } catch (EntityNotFoundException ex) {
            throw new RuntimeException(String.format("Wrong token definition. The token id: %d was not found.", tokenVO.getId()));
        }
    }
}
