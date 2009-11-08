/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.render;

import com.sinco.network.NetworkController;
import com.sinco.network.plugin.Attribute;
import com.sinco.network.plugin.JaguarPluginDefinition;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author cross
 */
public class RenderDataPlugin implements JaguarPluginDefinition {

    /**
     * Returns the request types supported by this plugin
     * @return
     */
    public List<Long> getRequestTypesSupported() {
        ArrayList<Long> supported = new ArrayList<Long>();
        supported.add(4L); // Get process definitions
        supported.add(5L); // Get form definitions
        return supported;
    }

    /**
     * Returns the controller class which will attend the request
     * @return
     */
    public Class<? extends NetworkController> getControllerClass() {
        return RenderNetworkController.class;
    }

    /**
     * Describes the parameters of the request method in the plugin controller
     * @return
     */
    public List<Attribute> getParatemers() {
        return new ArrayList<Attribute>();
    }
}
