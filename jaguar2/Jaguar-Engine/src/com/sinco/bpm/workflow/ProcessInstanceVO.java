/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import java.io.Serializable;

/**
 *
 * @author JuanC
 */
public class ProcessInstanceVO implements Serializable {
    private int id;
    private String processName;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getProcessName() {
        return processName;
    }

    public void setProcessName(String processName) {
        this.processName = processName;
    }
    
    @Override
    public String toString() {
        return "ProcessInstanceVO [id=" + getId() + ",ProcessName=" + getProcessName() + "]";
    }
}
