/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.render;

import com.sinco.network.NetworkClient;
import com.sinco.network.NetworkException;
import com.sinco.network.NetworkService;
import java.net.UnknownHostException;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class RenderNetworkControllerTest extends TestCase {
    
    public RenderNetworkControllerTest(String testName) {
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
     * Test of processRequest method, of class RenderNetworkController.
     */
    public void testGetProcessDefinitions() {
        try {
            System.out.println("GetProcessDefinitions");
            Long requestType = 4L;
            Object[] parameters = new Object[]{};
            NetworkClient client = new NetworkClient();
            Object[] result = client.sendReceive("localhost", NetworkService.PORT, requestType, parameters);
            System.out.println(result);
        } catch (UnknownHostException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        } catch (NetworkException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    /**
     * Test of processRequest method, of class RenderNetworkController.
     */
    public void testGetFormDefinitions() {
        try {
            System.out.println("GetFormDefinitions");
            Long requestType = 5L;
            Object[] parameters = new Object[]{};
            NetworkClient client = new NetworkClient();
            Object[] result = client.sendReceive("localhost", NetworkService.PORT, requestType, parameters);
            System.out.println(result);
        } catch (UnknownHostException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        } catch (NetworkException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

}
