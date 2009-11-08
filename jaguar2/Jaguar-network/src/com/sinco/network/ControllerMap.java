/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network;

/**
 *
 * @author cross
 */
class ControllerMap {
    private String name;
    private Class controllerClass;
    private Class requestClass;
    private Class responseClass;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Class getControllerClass() {
        return controllerClass;
    }

    public void setControllerClass(Class controllerClass) {
        this.controllerClass = controllerClass;
    }

    public Class getRequestClass() {
        return requestClass;
    }

    public void setRequestClass(Class requestClass) {
        this.requestClass = requestClass;
    }

    public Class getResponseClass() {
        return responseClass;
    }

    public void setResponseClass(Class responseClass) {
        this.responseClass = responseClass;
    }
}
