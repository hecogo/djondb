/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.persistence;

/**
 *
 * @author cross
 */
public class PersistenceException extends RuntimeException {

    public PersistenceException(Exception e) {
        super(e);
    }
    
    public PersistenceException() {
        super();
    }
    
    public PersistenceException(String message) {
        super(message);
    }
}
