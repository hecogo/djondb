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
public class RequestProcessToken extends Request implements Serializable {
    private int idProcessInstance;
    private TokenVO token;

    public RequestProcessToken(RequestAction action) {
        if (!RequestAction.PROCESSTOKEN.equals(action)) {
            throw new IllegalArgumentException("RequestAction is not valid. Requested Action: " + action.toString());
        }
        setAction(action);
    }
    
    public int getIdProcessInstance() {
        return idProcessInstance;
    }

    public void setIdProcessInstance(int idProcessInstance) {
        this.idProcessInstance = idProcessInstance;
    }

    public TokenVO getToken() {
        return token;
    }

    public void setToken(TokenVO token) {
        this.token = token;
    }
    
}
