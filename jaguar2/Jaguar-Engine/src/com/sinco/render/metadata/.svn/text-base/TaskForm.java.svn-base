/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.render.metadata;

import com.sinco.persistence.Entity;
import com.sinco.persistence.Id;
import java.io.Serializable;

/**
 *
 * @author cross
 */
@Entity
public class TaskForm implements Serializable {
    private long taskId;
    private int formId;

    public long getTaskId() {
        return taskId;
    }

    public void setTaskId(long taskId) {
        this.taskId = taskId;
    }

    public int getFormId() {
        return formId;
    }

    public void setFormId(int formId) {
        this.formId = formId;
    }

    @Id
    public String getId() {
        return taskId + "_" + formId;
    }

    public void setId(String id) {
        // TODO, remove when the entitymanager supports readonly ids
    }
}
