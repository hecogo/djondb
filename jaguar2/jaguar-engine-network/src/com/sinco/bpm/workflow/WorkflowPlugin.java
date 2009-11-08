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
public class WorkflowPlugin implements JaguarPluginDefinition {

    public List<Long> getRequestTypesSupported() {
        ArrayList<Long> requestTypes = new ArrayList<Long>(1);
        requestTypes.add(102L);
        requestTypes.add(103L);
        return requestTypes;
    }
    

    public Class<? extends NetworkController> getControllerClass() {
        return WorkflowNetworkController.class;
    }

    public List<Attribute> getParatemers() {
        ArrayList<Attribute> result = new ArrayList<Attribute>();
        Attribute attr = new Attribute();
        attr.setType(Integer.class);
        
        result.add(attr);
        
        return result;
    }

}
