/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.persistence;

import java.util.List;

/**
 *
 * @author cross
 */
public interface Query<T> {

    public List<T> getResultList();
    public T getSingleResult();

    public Query setParameter(String field, Object value);

}
