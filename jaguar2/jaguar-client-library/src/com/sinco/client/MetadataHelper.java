/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client;

import com.sinco.client.metadata.DigesterUtil;
import com.sinco.client.metadata.Form;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.cache.CacheFactory;
import com.sinco.cache.CacheGroup;
import com.sinco.client.controls.FormPanel;
import com.sinco.network.NetworkClient;
import com.sinco.network.NetworkException;
import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

/**
 *
 * @author cross
 */
public class MetadataHelper {
    public static final String FORMDEFINITIONS = "FORMDEFINITIONS";
    private static final String METADATAPREFIX = "METADATA_";
    private static final String PROCESSDEFINITIONS = "PROCESSDEFINITIONS";
    private Server server;
    
    public MetadataHelper(Server server) {
        this.server = server;
    }
    
    public ProcessDefinition[] loadProcessDefinitions() throws UnknownHostException, NetworkException {
        NetworkClient client = new NetworkClient();
        Long requestType = 4L;
        Object[] response = client.sendReceive(server.getHostAddress(), server.getHostPort(), requestType, new Object[]{});
        
        ProcessDefinition[] definitionsArray;
        definitionsArray = Arrays.copyOf(response, response.length, ProcessDefinition[].class);
        
        String cacheKey = String.format(METADATAPREFIX + getServer().getSessionId());
        CacheGroup globalCache = CacheFactory.getGlobalCache(cacheKey);
        globalCache.add( PROCESSDEFINITIONS, definitionsArray);
        
        return definitionsArray;
    }
    
    public ProcessDefinition[] getProcessDefinitions() throws UnknownHostException, NetworkException {
        String cacheKey = METADATAPREFIX + getServer().getSessionId();
        CacheGroup globalCache = CacheFactory.getGlobalCache(cacheKey);
        ProcessDefinition[] definitions = (ProcessDefinition[]) globalCache.get(PROCESSDEFINITIONS);
        if (definitions == null) {
            definitions = loadProcessDefinitions();
        }
        return definitions;
    } 

    public Server getServer() {
        return server;
    }

    public void setServer(Server server) {
        this.server = server;
    }

    public FormPanel[] getFormDefinitions() {
        try {
            String cacheKey = String.format(METADATAPREFIX + getServer().getSessionId());
            CacheGroup globalCache = CacheFactory.getGlobalCache(cacheKey);
            HashMap<Integer, FormPanel> forms = (HashMap<Integer, FormPanel>) globalCache.get(FORMDEFINITIONS);
            
            if (forms != null) {
                return forms.values().toArray(new FormPanel[] {});
            }
            
            forms = new HashMap<Integer, FormPanel>();
            
            NetworkClient client = new NetworkClient();
            Long requestType = 5L;
            Object[] response = client.sendReceive(getServer().getHostAddress(), getServer().getHostPort(), requestType, new Object[]{});

            for (Object objForm : response) {
                FormPanel pnl = (FormPanel) objForm;
                forms.put(pnl.getIdForm(), pnl);
            }
            globalCache.add(FORMDEFINITIONS, forms);
            
            return (FormPanel[]) forms.values().toArray();
        } catch (UnknownHostException ex) {
            throw new RuntimeException(ex);
        } catch (NetworkException ex) {
            throw new RuntimeException(ex);
        }
        
    }
}
