/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.workflow.metadata;

import java.util.ArrayList;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class ProcessDefinitionFacadeTest extends TestCase {

    public ProcessDefinitionFacadeTest(String testName) {
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
     * Test of testPersist method, of class ProcessDefinitionFacade.
     */
    public void testTestPersist() {
        System.out.println("testPersist");
        testPersist();
    }

    /**
     * Test of persist method, of class com.sinco.bpm.runtime.WorkflowFacadeBean.
     */
    public void testPersist() {
        System.out.println("persist");

        ProcessDefinitionFacade instance = new ProcessDefinitionFacade();
        
        ProcessDefinition def = new ProcessDefinition();
        def.setDefinitionName("With events2");
        def.setProcessType(ProcessType.NONE);

        StartEvent evt = new StartEvent();
        ArrayList<CommonEvent> events = new ArrayList<CommonEvent>();
        events.add(evt);
        def.setEvents(events);
        evt.setProcessDefinition(def);

        ManualTask task1 = new ManualTask();
        task1.setProcessDefinition(def);
        task1.setActivityType(ActivityType.TASK);
        task1.setLoopType(LoopType.NONE);
        task1.setStartQuantity(1);
        task1.setTaskType(TaskType.MANUAL);

        ArrayList<ActivityCommon> lst = new ArrayList<ActivityCommon>();
        lst.add(task1);

        def.setTasks(lst);

        ArrayList<CommonConector> sequenceFlows1 = new ArrayList<CommonConector>();
        SequenceFlow flow = new SequenceFlow();
        flow.setQuantity(1);
        flow.setSource(evt);
        flow.setTarget(task1);
        sequenceFlows1.add(flow);
        evt.setSequenceFlows(sequenceFlows1);

        instance.create(def);
    }
}
