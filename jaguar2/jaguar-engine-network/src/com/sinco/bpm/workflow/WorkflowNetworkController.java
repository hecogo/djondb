/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.workflow;

import com.sinco.bpm.metadata.deployment.DeploymentFacade;
import com.sinco.network.AbstractNetworkRequest;
import com.sinco.network.AbstractNetworkResponse;
import com.sinco.network.NetworkController;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class WorkflowNetworkController implements NetworkController {

    private static Log logger = LogFactory.getLog(WorkflowNetworkController.class);

    public Object[] processRequest(Long requestType, Object... parameters) {
        switch (requestType.intValue()) {
            case 102:
                return createInstance(parameters);
            case 103:
                return processToken(parameters);
            default:
                throw new IllegalArgumentException(String.format("The request type %d is not supported", requestType));
        }
    }

    private Object[] createInstance(Object[] parameters) {
        RequestProcessAction request = new RequestProcessAction();
        request.setAction(RequestAction.CREATEINSTANCE);
        long procdef = (Long) parameters[0];
        request.setProcessDefinition(procdef);

        WorkflowController instance = new WorkflowController();
        WorkflowResponse result = instance.processAction(request);

        return new Object[]{result};
    }

    private Object[] processToken(Object[] parameters) {
        RequestProcessToken processToken = new RequestProcessToken(RequestAction.PROCESSTOKEN);
        TokenVO token = (TokenVO) parameters[0];
        processToken.setIdProcessInstance(token.getProcessInstance().getId());
        processToken.setToken(token);
        
        WorkflowController controller = new WorkflowController();

        WorkflowResponse response = controller.processAction(processToken);

        return new Object[] {response};
    }
}
