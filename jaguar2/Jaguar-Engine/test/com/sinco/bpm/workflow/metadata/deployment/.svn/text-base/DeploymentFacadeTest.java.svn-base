/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow.metadata.deployment;

import com.sinco.bpm.metadata.deployment.DeploymentFacade;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class DeploymentFacadeTest extends TestCase {
    
    public DeploymentFacadeTest(String testName) {
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
     * Test of deploy method, of class DeploymentFacadeBean.
     */
    public void testDeploy() throws IOException {
        System.out.println("deploy");
        InputStream xml = getClass().getResourceAsStream("/com/sinco/bpm/workflow/metadata/deployment/sample1.xml");
        BufferedReader reader = new BufferedReader(new InputStreamReader(xml));
        String line;
        StringBuffer xmltext = new StringBuffer();
        while ((line = reader.readLine()) != null) {
            xmltext.append(line);
        }
        reader.close();
        DeploymentFacade instance = new DeploymentFacade();
        System.out.println("Created: " + instance.deploy(xmltext.toString()));
    }

}
