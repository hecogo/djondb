/*
 * TaskType.java
 *
 * Created on 7 July 2007, 12:33
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow.metadata;

/**
 *
 * @author cross
 */
public enum TaskType {
    SERVICE,
    RECEIVE,
    SEND,
    USER,
    SCRIPT,
    MANUAL,
    REFERENCE,
    NONE;
    
    public boolean equals(TaskType obj) {
        if (!(obj instanceof TaskType)) {
            return false;
        }
        return (obj.ordinal() == ordinal());
    }
}
