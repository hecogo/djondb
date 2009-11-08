/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.metadata.deployment;

import com.sinco.bpm.workflow.metadata.ManualTask;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.ProcessDefinitionFacade;
import com.sinco.persistence.EntityManagerFactory;
import com.sinco.persistence.EntityManagerType;
import com.sinco.render.metadata.TaskForm;
import java.io.ByteArrayInputStream;

/**
 *
 * @author cross
 */
public class DeploymentFacade {

    public long deploy(String processXML) {
        Process process = new DigesterUtil().processXML(new ByteArrayInputStream(processXML.getBytes()));

        ProcessDefinition def = process.getProcessDefinition(process);

        ProcessDefinitionFacade processDefinitionFacade = new ProcessDefinitionFacade();

        processDefinitionFacade.create(def);

        deployForms(process);

        return def.getId();
    }

    private void deployForms(Process process) {
        for (Task tsk : process.getTasks()) {
            if (tsk.getForm() != 0) {
                TaskForm tskForm = new TaskForm();
                tskForm.setTaskId(tsk.getId());
                tskForm.setFormId(tsk.getForm());

                EntityManagerFactory.getEntityManager(EntityManagerType.METADATA).persist(tskForm);
            }
        }
    }
}
