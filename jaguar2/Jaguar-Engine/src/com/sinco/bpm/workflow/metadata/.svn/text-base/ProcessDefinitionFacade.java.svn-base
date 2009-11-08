/*
 * ProcessDefinitionFacade.java
 *
 * Created on 4 January 2008, 12:17
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow.metadata;

import com.sinco.persistence.EntityManager;
import com.sinco.persistence.EntityManagerFactory;
import com.sinco.persistence.EntityManagerType;
import com.sinco.persistence.EntityNotFoundException;
import java.util.List;

/**
 *
 * @author cross
 */
public class ProcessDefinitionFacade {

    private EntityManager entityManager;
    
    /** Creates a new instance of ProcessDefinitionFacade */
    public ProcessDefinitionFacade() {
        entityManager = EntityManagerFactory.getEntityManager(EntityManagerType.METADATA);
    }

    public void create(ProcessDefinition processDefinition) {
        entityManager.persist(processDefinition);
    }

    public void edit(ProcessDefinition processDefinition) {
        entityManager.merge(processDefinition);
    }

    public void destroy(ProcessDefinition processDefinition) {
        entityManager.merge(processDefinition);
        entityManager.remove(processDefinition);
    }

    public ProcessDefinition find(Object pk) throws EntityNotFoundException {
        return (ProcessDefinition) entityManager.find(ProcessDefinition.class, pk);
    }

    public List findAll() {
        List results = entityManager.createQuery("select object(o) from ProcessDefinition as o").getResultList();
        return results;
    }
    
}
