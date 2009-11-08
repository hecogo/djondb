/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.persistence;

import java.util.Collection;


/**
 *
 * @author cross
 */
public interface EntityManager {

    public Query createNamedQuery(String string);

    public Query createQuery(String string);

    public <T> T find(Class<T> aClass, Object id) throws EntityNotFoundException;

    public <T> Collection<T> findAll(Class<T> aClass);
    
    public <T> T persist(T entity);
    public <T> T merge(T entity);
    public void remove(Object entity);
}
