/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.workflow;

import com.sinco.persistence.EntityManager;
import com.sinco.persistence.EntityNotFoundException;
import java.util.List;

/**
 *
 * @author cross
 */
public class WorkflowController {

    private EntityManager em;

    public WorkflowResponse processAction(Request request) {
        WorkflowFacade workflowFacade = new WorkflowFacade();
        ProcessInstanceFacade processInstanceFacade = new ProcessInstanceFacade();
        switch (request.getAction()) {
            case CREATEINSTANCE: {
                RequestProcessAction processAction = (RequestProcessAction) request;
                ProcessInstance createProcessInstance;
                try {
                    createProcessInstance = workflowFacade.createProcessInstance(processAction.getProcessDefinition());
                } catch (EntityNotFoundException ex) {
                    throw new RuntimeException(String.format("Wrong process definition. Exception: %s", ex.getMessage()));
                }
                List<Token> currentTokens = createProcessInstance.getCurrentTokens();
                WorkflowResponse response = new WorkflowResponse();
                List<TokenVO> tokenVOs = TransferObjectAssembler.getInstance().getToken(TransferObjectAssembler.TokenStructure.BASIC, currentTokens);
                response.setCurrentTokens(tokenVOs);
                return response;
            }
            case PROCESSTOKEN: {
                RequestProcessToken processToken = (RequestProcessToken) request;
                ProcessInstance instance;
                try {
                    instance = processInstanceFacade.find(processToken.getIdProcessInstance());
                } catch (EntityNotFoundException ex) {
                    throw new RuntimeException(String.format("Wrong token definition. The process instance %d was not found", processToken.getIdProcessInstance()));
                }
                List<Token> newTokens = workflowFacade.processToken(instance, processToken.getToken());
                WorkflowResponse response = new WorkflowResponse();
                List<TokenVO> tokenVOs = TransferObjectAssembler.getInstance().getToken(TransferObjectAssembler.TokenStructure.BASIC, newTokens);
                response.setCurrentTokens(tokenVOs);

                return response;
            }
            default:
                throw new UnsupportedOperationException("Unsupported action " + request.getAction());
        }
    }
}
