/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import com.sinco.bpm.workflow.metadata.ActivityStatus;
import com.sinco.bpm.workflow.metadata.ActivityType;
import com.sinco.bpm.workflow.metadata.CommonConector;
import com.sinco.bpm.workflow.metadata.ManualTask;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.SequenceFlow;
import com.sinco.bpm.workflow.metadata.ServiceTask;
import com.sinco.bpm.workflow.metadata.Task;
import com.sinco.bpm.workflow.metadata.TaskType;
import java.util.ArrayList;
import java.util.List;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class TokenFacadeTest extends TestCase {
    
    public TokenFacadeTest(String testName) {
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
     * Test of processToken method, of class TokenFacadeBean.
     */
    public void testProcessToken() {
        System.out.println("processToken");
        ProcessInstance process = new ProcessInstance();
        ProcessDefinition def = new ProcessDefinition();
        def.setDefinitionName("Test");
        Token start = new Token();
        start.setProcessInstance(process);
        start.setStatus(TokenStatus.NONE);
        Task auto = new ServiceTask();
        auto.setProcessDefinition(def);
        List<CommonConector> seq1 = new ArrayList<CommonConector>();
        SequenceFlow flow1 = new SequenceFlow();
        
        Task manual = new ManualTask();
        manual.setActivityType(ActivityType.TASK);
        manual.setProcessDefinition(def);
        manual.setStatus(ActivityStatus.NONE);
        manual.setTaskType(TaskType.MANUAL);
        
        flow1.setSource(auto);
        flow1.setTarget(manual);
        seq1.add(flow1);
        
        auto.setSequenceFlows(seq1);
        auto.setActivityType(ActivityType.TASK);
        auto.setProcessDefinition(def);
        auto.setTaskType(TaskType.SERVICE);
        
        start.setTask(auto);
        
        TokenFacade instance = new TokenFacade();
        List<Token> result = instance.processToken(process, start);
    }

}
