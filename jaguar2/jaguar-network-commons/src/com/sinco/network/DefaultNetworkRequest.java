/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network;

/**
 *
 * @author cross
 */
public class DefaultNetworkRequest extends AbstractNetworkRequest {
    private Object value;
    
    public void setValue(Object value) {
        this.value = value;
    }
    
    @Override
    public Object getValue() {
        return value;
    }

}
