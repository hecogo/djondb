/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.persistence;

/**
 *
 * @author cross
 */
public class EntityNotFoundException extends Exception {
    private String message;
    
    public EntityNotFoundException(Class aClass, Object primaryKey) {
        message = String.format("Class: %s with primary key %s was not found", aClass.getName(), primaryKey.toString());
    }
    
    @Override
    public String getMessage() {
        return message;
    }

}
