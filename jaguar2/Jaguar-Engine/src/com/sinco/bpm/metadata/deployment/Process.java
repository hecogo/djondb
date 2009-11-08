/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.metadata.deployment;

import com.sinco.bpm.workflow.metadata.ActivityCommon;
import com.sinco.bpm.workflow.metadata.CommonEvent;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.ProcessType;
import com.sinco.persistence.Entity;
import java.util.ArrayList;
import java.util.Collection;

/**
 *
 * @author cross
 */
@Entity
public class Process {
    private String name;
    private String masterEntity;
    private Collection<Event> events = new ArrayList<Event>();
    private Collection<Task> tasks = new ArrayList<Task>();
    private Collection<Form> forms = new ArrayList<Form>();

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void addEvent(Event evt) {
        events.add(evt);
    }
    
    public Collection<Event> getEvents() {
        return events;
    }

    public void setEvents(Collection<Event> events) {
        this.events = events;
    }

    public void addTask(Task task) {
        tasks.add(task);
    }
    
    public Collection<Task> getTasks() {
        return tasks;
    }

    public void setTasks(Collection<Task> tasks) {
        this.tasks = tasks;
    }
    
    public Task getTask(int id) {
        for (Task task : tasks) {
            if (task.getId() == id) {
                return task;
            }
        }
        return null;
    }
    
    public ProcessDefinition getProcessDefinition(Process process) {
        ProcessDefinition def = new ProcessDefinition();
        def.setDefinitionName(getName());
        def.setProcessType(ProcessType.NONE);
        def.setMasterEntity(getMasterEntity());
        
        ArrayList<ActivityCommon> newTasks = new ArrayList<ActivityCommon>();
        for (Task task : getTasks() ) {
            com.sinco.bpm.workflow.metadata.Task newTask = task.getTaskDefinition(process, def);
            newTasks.add(newTask);
        }
        def.setTasks(newTasks);
        
        ArrayList<CommonEvent> newEvents = new ArrayList<CommonEvent>();
        for (Event evt : getEvents()) {
            newEvents.add(evt.getEventDef(process, def));
        }
        def.setEvents(newEvents);

        return def;
    }

    public Event getEvents(int eventId) {
        for (Event evt : events) {
            if (evt.getId() == eventId) {
                return evt;
            }
        }
        return null;
    }

    public String getMasterEntity() {
        return masterEntity;
    }

    public void setMasterEntity(String masterEntity) {
        this.masterEntity = masterEntity;
    }

    public void addForm(Form form) {
        forms.add(form);
    }
    public Collection<Form> getForms() {
        return forms;
    }

    public void setForms(Collection<Form> forms) {
        this.forms = forms;
    }
    
    public Form getForm(int id) {
        for (Form form : forms) {
            if (form.getId() == id) {
                return form;
            }
        }
        return null;
    }
}
