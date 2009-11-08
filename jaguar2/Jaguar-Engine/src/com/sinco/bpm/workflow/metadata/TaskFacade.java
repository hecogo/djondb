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
public class TaskFacade {
    private EntityManager em;

    public void create(Task task) {
        em.persist(task);
    }

    public void edit(Task task) {
        em.merge(task);
    }

    public void remove(Task task) {
        em.remove(em.merge(task));
    }

    public Task find(Object id) throws EntityNotFoundException {
        return em.find(com.sinco.bpm.workflow.metadata.Task.class, id);
    }

    public List<Task> findAll() {
        return em.createQuery("select object(o) from Task as o").getResultList();
    }

    public List<Task> findBy(ProcessDefinition def, TaskType taskType) {
        Query qry = em.createQuery("select object(o) from Task as o where o.processDefinition = :def and taskType = :type");
        qry.setParameter("def", def);
        qry.setParameter("type", taskType);
        return (List<Task>)qry.getResultList();
    }
}
