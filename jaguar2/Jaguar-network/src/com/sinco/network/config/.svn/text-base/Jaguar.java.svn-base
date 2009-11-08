/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network.config;

import java.util.ArrayList;

/**
 *
 * @author cross
 */
public class Jaguar {
    private ArrayList<Controller> controllers;
    private String workDir = System.getProperty("java.io.tmpdir");

    public ArrayList<Controller> getControllers() {
        return controllers;
    }

    public void setControllers(ArrayList<Controller> controllers) {
        this.controllers = controllers;
    }
    
    public void addController(Controller controller) {
        if (controllers == null) controllers = new ArrayList<Controller>();
        controllers.add(controller);
    }

    public String getWorkDir() {
        return workDir;
    }

    public void setWorkDir(String workDir) {
        this.workDir = workDir;
    }
    
    
}
