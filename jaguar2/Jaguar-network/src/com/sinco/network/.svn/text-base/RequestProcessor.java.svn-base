/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.network;

import com.sinco.cache.CacheFactory;
import com.sinco.cache.CacheGroup;
import com.sinco.network.plugin.Attribute;
import com.sinco.network.plugin.JaguarPluginDefinition;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class RequestProcessor {

    private static Log logger = LogFactory.getLog(RequestProcessor.class);

    public Object[] processRequest(Long requestType, ObjectInputStream ois) {

        if (logger.isDebugEnabled()) {
            logger.debug("Starting process request");
        }
        Object[] responses = null;
        try {
            JaguarPluginDefinition pluginDefinition = getPluginDefinition(requestType);
            Object[] requestParameters = getRequest(pluginDefinition, ois);
            responses = processRequest(requestType, requestParameters);
        } catch (InvalidRequestException e) {
            // TODO: Create an exception response
            }
        if (logger.isDebugEnabled()) {
            logger.debug("Writing socket response");
        }
        return responses;
    }

    public Object[] processRequest(Long requestType, Object[] requests) throws InvalidRequestException {
        try {
            JaguarPluginDefinition pluginDefinition = getPluginDefinition(requestType);
            if (pluginDefinition == null) {
                throw new IllegalArgumentException(String.format("RequestType %d not found.", requestType));
            }
            NetworkController controller = (NetworkController) pluginDefinition.getControllerClass().newInstance();

            Object[] response = controller.processRequest(requestType, requests);

            return response;
        } catch (InstantiationException ex) {
            throw new RuntimeException(ex);
        } catch (IllegalAccessException ex) {
            throw new RuntimeException(ex);
        }
    }

    private JaguarPluginDefinition getPluginDefinition(Long requestType) {
        CacheGroup globalCache = CacheFactory.getGlobalCache(NetworkService.SERVICE_GLOBALKEY);
        @SuppressWarnings(value = "unchecked")
        HashMap<Long, JaguarPluginDefinition> definitions = (HashMap<Long, JaguarPluginDefinition>) globalCache.get(NetworkService.PLUGINDEFINITIONS);
        JaguarPluginDefinition pluginDefinition = definitions.get(requestType);

        return pluginDefinition;
    }

    private Object[] getRequest(JaguarPluginDefinition pluginDefinition, ObjectInputStream ois) throws InvalidRequestException {
        List<Attribute> parameters = pluginDefinition.getParatemers();
        ArrayList result = new ArrayList();
        try {
            for (Attribute attr : parameters) {
                result.add(ois.readObject());
            }
            return result.toArray();
        } catch (IOException ex) {
            throw new InvalidRequestException(ex.getMessage());
        } catch (ClassNotFoundException ex) {
            throw new InvalidRequestException(ex.getMessage());
        }
    }
}
