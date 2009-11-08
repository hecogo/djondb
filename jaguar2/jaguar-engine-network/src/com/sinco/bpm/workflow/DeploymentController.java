/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import com.sinco.bpm.metadata.deployment.DeploymentFacade;
import com.sinco.network.NetworkController;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class DeploymentController implements NetworkController {
    private static Log logger = LogFactory.getLog(DeploymentController.class);
    
    public Object[] processRequest(Long requestType, Object... parameters) {
        if (logger.isDebugEnabled()) logger.debug("DeploymentController.processRequest");
        
        String xml = (String)parameters[0];
        DeploymentFacade facade = new DeploymentFacade();
        long definition = facade.deploy(xml);
        
        return new Object[] {definition};
    }

}
