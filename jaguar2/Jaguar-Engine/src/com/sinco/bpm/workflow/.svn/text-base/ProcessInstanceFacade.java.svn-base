/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import com.sinco.persistence.EntityManager;
import com.sinco.persistence.EntityManagerFactory;
import com.sinco.persistence.EntityManagerType;
import com.sinco.persistence.EntityNotFoundException;
import java.util.List;

/**
 *
 * @author cross
 */
public class ProcessInstanceFacade {

    private EntityManager entityManager;
    
    public ProcessInstanceFacade() {
        entityManager = EntityManagerFactory.getEntityManager(EntityManagerType.DATA);
    }
    
    public void create(ProcessInstance processInstance) {
        entityManager.persist(processInstance);
    }

    public void edit(ProcessInstance processInstance) {
        entityManager.merge(processInstance);
    }

    public void remove(ProcessInstance processInstance) {
        entityManager.remove(entityManager.merge(processInstance));
    }

    public ProcessInstance find(Object id) throws EntityNotFoundException {
        return entityManager.find(com.sinco.bpm.workflow.ProcessInstance.class, id);
    }

    @SuppressWarnings("unchecked")
    public List<ProcessInstance> findAll() {
        return entityManager.createQuery("select object(o) from ProcessInstance as o").getResultList();
    }

}
