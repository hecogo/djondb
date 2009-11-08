/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import com.sinco.bpm.workflow.WorkflowResponse;
import com.sinco.bpm.workflow.RequestAction;
import com.sinco.bpm.workflow.RequestProcessAction;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class WorkflowControllerTest extends TestCase {
    
    public WorkflowControllerTest(String testName) {
        super(testName);
    }            

    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    /**
     * Test of processAction method, of class WorkflowControllerBean.
     */
    public void testProcessAction() {
        System.out.println("processAction");
        RequestProcessAction request = new RequestProcessAction();
        request.setAction(RequestAction.CREATEINSTANCE);
        request.setProcessDefinition(102L);
        
        WorkflowController instance = new WorkflowController();
        WorkflowResponse expResult = null;
        WorkflowResponse result = instance.processAction(request);
        assertEquals(WorkflowResponse.class, result.getClass());
    }
    
    public void testProcessActionProcessToken() {
        System.out.println("processActionToken");
        RequestProcessAction request = new RequestProcessAction();
        request.setAction(RequestAction.CREATEINSTANCE);
        request.setProcessDefinition(103L);
        
        WorkflowController instance = new WorkflowController();
        WorkflowResponse expResult = null;
        WorkflowResponse result = instance.processAction(request);

        for (TokenVO token : result.getCurrentTokens()) {
            RequestProcessToken processToken = new RequestProcessToken(RequestAction.PROCESSTOKEN);
            processToken.setIdProcessInstance(token.getProcessInstance().getId());
            processToken.setToken(token);
            result = instance.processAction(processToken);
        }
    }

}
