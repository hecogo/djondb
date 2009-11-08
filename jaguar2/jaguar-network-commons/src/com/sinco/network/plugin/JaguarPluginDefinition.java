/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network.plugin;

import com.sinco.network.NetworkController;
import java.util.List;

/**
 *
 * @author cross
 */
public interface JaguarPluginDefinition {

    /**
     * Returns the request types supported by this plugin
     * @return
     */
    public List<Long> getRequestTypesSupported();
    
    /**
     * Returns the controller class which will attend the request
     * @return
     */
    Class<? extends NetworkController> getControllerClass();

    /**
     * Describes the parameters of the request method in the plugin controller
     * @return
     */
    List<Attribute> getParatemers();
    
}
