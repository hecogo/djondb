/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.client.model;

import com.sinco.bpm.workflow.DeploymentPlugin;
import com.sinco.network.AbstractNetworkResponse;
import com.sinco.network.NetworkClient;
import com.sinco.network.NetworkException;
import java.net.UnknownHostException;

/**
 *
 * @author cross
 */
public class Deployment {

    private String xmlDefinition;
    private long processDefinition;

    public void deploy() throws UnknownHostException, NetworkException {
        NetworkClient client = new NetworkClient();

        Long requestType = new DeploymentPlugin().getRequestTypesSupported().iterator().next();
        Object[] response = client.sendReceive("localhost", 1048, requestType, new Object[] {getXmlDefinition()});
        processDefinition = (Long)response[0];
    }

    public long getProcessDefinition() {
        return processDefinition;
    }

    public void setProcessDefinition(long processDefinition) {
        this.processDefinition = processDefinition;
    }

    public String getXmlDefinition() {
        return xmlDefinition;
    }

    public void setXmlDefinition(String xmlDefinition) {
        this.xmlDefinition = xmlDefinition;
    }
}
