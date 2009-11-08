/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.client.model;

import com.sinco.cache.CacheFactory;
import com.sinco.client.Server;
import com.sinco.network.NetworkClient;
import com.sinco.network.NetworkException;
import com.sinco.render.metadata.TaskForm;
import java.net.UnknownHostException;
import java.util.Collection;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author cross
 */
public class MetadataModel {

    private Server server;

    public MetadataModel(Server server) {
        this.server = server;
    }

    public void loadFormDefinitions() throws UnknownHostException {
        try {
            NetworkClient client = new NetworkClient();
            Object[] response = client.sendReceive(server.getHostAddress(), server.getHostPort(), 5, new Object[]{});
            HashMap<Integer, byte[]> forms = (HashMap<Integer, byte[]>) response[0];

            Collection<TaskForm> taskForms = (Collection<TaskForm>) response[1];

            // Loads the forms into the current classloader
            HashMap<Integer, Class> loadedForms = new HashMap<Integer, Class>(forms.size());
            for (Integer formId : forms.keySet()) {
                byte[] classData = forms.get(formId);

                Class formClass = com.sinco.util.ClassLoader.getInstance().loadClass(classData);
                loadedForms.put(formId, formClass);
            }

            HashMap<Long, Class> taskFormByTask = new HashMap<Long, Class>();
            for (TaskForm tskForm : taskForms) {
                Class formClass = loadedForms.get(tskForm.getFormId());
                if (formClass != null) {
                    taskFormByTask.put(tskForm.getTaskId(), formClass);
                }
            }
            CacheFactory.getGlobalCache("METADATA").add("TASKFORMS", taskFormByTask);
        } catch (NetworkException ex) {
            throw new RuntimeException(ex);
        }
    }
}
