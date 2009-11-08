/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import com.sinco.network.NetworkController;
import com.sinco.network.plugin.Attribute;
import com.sinco.network.plugin.JaguarPluginDefinition;
import com.sinco.network.plugin.Plugin;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author cross
 */
@Plugin
public class DeploymentPlugin implements JaguarPluginDefinition {

    public List<Long> getRequestTypesSupported() {
        ArrayList<Long> requestTypes = new ArrayList<Long>(1);
        requestTypes.add(101L);
        return requestTypes;
    }
    
    public Class<? extends NetworkController> getControllerClass() {
        return DeploymentController.class;
    }

    public List<Attribute> getParatemers() {
        ArrayList<Attribute> parameters = new ArrayList<Attribute>(1);
        Attribute attr = new Attribute();
        attr.setType(String.class);
        parameters.add(attr);
        
        return parameters;
    }

    public List<Long> getRequestType() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

}
