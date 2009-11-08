/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow.metadata;

import com.sinco.persistence.EntityManager;
import com.sinco.persistence.EntityNotFoundException;
import com.sinco.persistence.Query;
import java.util.List;

/**
 *
 * @author cross
 */
public class EventFacade {
    private EntityManager em;

    public List<CommonEvent> findBy(ProcessDefinition def, EventType type) {
        Query qry = em.createNamedQuery("findByProcessDefinitionEventType");
        qry.setParameter("eventType", type);
        qry.setParameter("processDefinition", def);
        
        return (List<CommonEvent>)qry.getResultList();
    }

    public void persist(CommonEvent evt) {
        em.persist(evt);
    }
    
    public CommonEvent find(Object pk) throws EntityNotFoundException {
        return em.find(CommonEvent.class, pk);
    }
    
    public void create(CommonEvent evt) {
        em.persist(evt);
    }
    
    public void edit(CommonEvent evt) {
        em.merge(evt);
    }
}
