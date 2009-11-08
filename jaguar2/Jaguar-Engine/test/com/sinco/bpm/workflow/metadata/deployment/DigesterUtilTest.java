/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow.metadata.deployment;

import com.sinco.bpm.metadata.deployment.DigesterUtil;
import com.sinco.bpm.metadata.deployment.Process;
import java.io.InputStream;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class DigesterUtilTest extends TestCase {
    
    public DigesterUtilTest(String testName) {
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
     * Test of processXML method, of class DigesterUtil.
     */
    public void testProcessXML() {
        System.out.println("processXML");
        InputStream xml = getClass().getResourceAsStream("/com/sinco/bpm/workflow/metadata/deployment/sample1.xml");
        DigesterUtil instance = new DigesterUtil();
        Process result = instance.processXML(xml);
        assertTrue(result.getEvents().iterator().next().getSequenceFlows().size() > 0);
        assertEquals(1, result.getEvents().iterator().next().getSequenceFlows().iterator().next().getTargets().size());
    }

}
