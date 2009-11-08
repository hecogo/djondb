/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.metadata.deployment;

/**
 *
 * @author cross
 */
public class Target {
    private int taskId;
    private int eventId;

    public Target() {
    }
    
    public int getTaskId() {
        return taskId;
    }

    public void setTaskId(int taskId) {
        this.taskId = taskId;
    }

    public int getEventId() {
        return eventId;
    }

    public void setEventId(int eventId) {
        this.eventId = eventId;
    }
}
