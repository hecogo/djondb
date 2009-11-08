/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

/**
 *
 * @author cross
 */
public enum TokenStatus {
    NONE,
    STARTED,
    USER,
    POSTUSER,
    ENDED;
            
    public boolean equals(TokenStatus status) {
        if (!(status instanceof TokenStatus)) {
            return false;
        }
        if (status == null) {
            return false;
        }
        return (status.ordinal() == ordinal());
    }
}
