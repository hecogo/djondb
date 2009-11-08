/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.render;

import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.ProcessDefinitionFacade;
import com.sinco.cache.CacheFactory;
import com.sinco.network.NetworkController;
import com.sinco.persistence.EntityManagerFactory;
import com.sinco.persistence.EntityManagerType;
import com.sinco.persistence.EntityNotFoundException;
import com.sinco.render.metadata.TaskForm;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class RenderNetworkController implements NetworkController {

    private static Log logger = LogFactory.getLog(RenderNetworkController.class);

    public Object[] processRequest(Long requestType, Object... parameters) {
        if (logger.isDebugEnabled()) {
            logger.debug("RenderNetworkController.processRequest");
        }
        Object[] result;
        switch (requestType.intValue()) {
            case 4:
                result = getProcessDefinitions();
                break;
            case 5:
                result = getFormDefinitions();
                break;
            default:
                throw new IllegalArgumentException(String.format("RequestType %d not supported", requestType));
        }
        return result;
    }

    private Object[] getFormDefinitions() {
        HashMap<Integer, byte[]> forms = (HashMap<Integer, byte[]>) CacheFactory.getGlobalCache("METADATA").get("FORMS");

        ArrayList<TaskForm> taskFormRelations = getTaskFormRelations();
        
        return new Object[] {forms, taskFormRelations};
    }

    private ProcessDefinition[] getProcessDefinitions() {
        try {
            ProcessDefinitionFacade procDefFacade = new ProcessDefinitionFacade();
            //List<ProcessDefinition> definitions = procDefFacade.findAll();
            ArrayList<ProcessDefinition> definitions = new ArrayList<ProcessDefinition>();
            logger.info("Returning a temporal list, should be implemented with findAll");
            definitions.add(procDefFacade.find(1));

            return definitions.toArray(new ProcessDefinition[]{});
        } catch (EntityNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private ArrayList<TaskForm> getTaskFormRelations() {
        ArrayList<TaskForm> result = (ArrayList<TaskForm>) CacheFactory.getGlobalCache("METADATA").get("TASKFORM");
        if (result != null) {
            return result;
        }
        
        Collection<TaskForm> found = EntityManagerFactory.getEntityManager(EntityManagerType.METADATA).findAll(TaskForm.class);
        result = new ArrayList<TaskForm>(found);
        
        CacheFactory.getGlobalCache("METADATA").add("TASKFORM", result);
        return result;
    }
}
