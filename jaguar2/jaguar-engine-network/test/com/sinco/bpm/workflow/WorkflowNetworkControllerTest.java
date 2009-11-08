/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.workflow;

import com.sinco.network.NetworkClient;
import com.sinco.network.NetworkException;
import com.sinco.network.NetworkService;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.UnknownHostException;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class WorkflowNetworkControllerTest extends TestCase {

    public WorkflowNetworkControllerTest(String testName) {
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
     * Test of processRequest method, of class WorkflowNetworkController.
     */
    public void testNetworkDeploy() {
        try {
            System.out.println("NetworkDeploy");

            // Reading the xml file
            InputStream xml = getClass().getResourceAsStream("/processdefinition.xml");
            BufferedReader reader = new BufferedReader(new InputStreamReader(xml));
            String line;
            StringBuffer xmltext = new StringBuffer();
            while ((line = reader.readLine()) != null) {
                xmltext.append(line);
            }
            reader.close();

            // Creating network client
            System.out.println("sendingData");

            NetworkClient client = new NetworkClient();
            Long requestType = new DeploymentPlugin().getRequestTypesSupported().iterator().next();
            Object obj = client.sendReceive(InetAddress.getLocalHost().getHostName(), NetworkService.PORT, requestType, new Object[] {xmltext.toString() } );

            System.out.println(obj);
        } catch (UnknownHostException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        } catch (NetworkException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        } catch (IOException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    /**
     * Test of processRequest method, of class WorkflowNetworkController.
     */
    public void testCreateInstance() {
        try {
            System.out.println("CreateInstance");
            Object[] request = new Object[2];
            
            request[0] = 1L;

            // Creating network client
            System.out.println("sendingData");

            NetworkClient client = new NetworkClient();
            Long requestType = 102L;
            
            Object obj = client.sendReceive(InetAddress.getLocalHost().getHostName(), NetworkService.PORT, requestType, request);

            System.out.println(obj);
        } catch (UnknownHostException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        } catch (NetworkException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        } catch (IOException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }
}
