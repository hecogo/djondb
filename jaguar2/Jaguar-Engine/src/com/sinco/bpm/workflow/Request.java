/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import java.io.Serializable;

/**
 *
 * @author cross
 */
public abstract class Request implements Serializable {
    private RequestAction action;

    public RequestAction getAction() {
        return action;
    }

    public void setAction(RequestAction action) {
        this.action = action;
    }

}
