/*
 * WorkflowFacadeTest.java
 * JUnit based test
 *
 * Created on 8 July 2007, 22:18
 */
package com.sinco.bpm.workflow;

import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.ProcessDefinitionFacade;
import com.sinco.persistence.EntityNotFoundException;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class WorkflowFacadeTest extends TestCase {

    public WorkflowFacadeTest(String testName) {
        super(testName);
    }

    protected void setUp() throws Exception {
    }

    protected void tearDown() throws Exception {
    }

    /**
     * Test of createProcessInstance method, of class com.sinco.bpm.runtime.WorkflowFacadeBean.
     */
    public void testCreateProcessInstance() {
        try {
            ProcessDefinitionFacade instance = new ProcessDefinitionFacade();
            ProcessDefinition def = instance.find(new Integer(1));
            System.out.println("createProcessInstance");

            WorkflowFacade facade = new WorkflowFacade();

            facade.createProcessInstance(def);
        } catch (EntityNotFoundException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }
}
