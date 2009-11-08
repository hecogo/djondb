/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.client;

import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.client.controls.FormPanel;
import com.sinco.network.NetworkException;
import java.net.UnknownHostException;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class MetadataHelperTest extends TestCase {

    public MetadataHelperTest(String testName) {
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
     * Test of loadProcessDefinitions method, of class ProcessHelper.
     */
    public void testLoadProcessDefinitions() {
        try {
            System.out.println("loadProcessDefinitions");
            Server server = new Server();
            server.setHostAddress("localhost");
            server.setHostPort(1048);
            server.setLogged(true);
            server.setPrivateKey("sslkeytest");
            server.setSessionId("ASDFGHJKTQUIIGHA");
            server.setUserName("cross");

            MetadataHelper instance = new MetadataHelper(server);
            ProcessDefinition[] result = instance.loadProcessDefinitions();
            assertNotNull(result);
        } catch (UnknownHostException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        } catch (NetworkException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    /**
     * Test of getProcessDefinitions method, of class ProcessHelper.
     */
    public void testGetProcessDefinitions() throws Exception {
        System.out.println("getProcessDefinitions");
        try {
            Server server = new Server();
            server.setHostAddress("localhost");
            server.setHostPort(1048);
            server.setLogged(true);
            server.setPrivateKey("sslkeytest");
            server.setSessionId("ASDFGHJKTQUIIGHA");
            server.setUserName("cross");

            MetadataHelper instance = new MetadataHelper(server);
            ProcessDefinition[] result = instance.getProcessDefinitions();
            assertNotNull(result);
        } catch (UnknownHostException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        } catch (NetworkException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    public void testGetFormDefinitions() throws Exception {
        System.out.println("getFormDefinitions");
        Server server = new Server();
        server.setHostAddress("localhost");
        server.setHostPort(1048);
        server.setLogged(true);
        server.setPrivateKey("sslkeytest");
        server.setSessionId("ASDFGHJKTQUIIGHA");
        server.setUserName("cross");

        MetadataHelper instance = new MetadataHelper(server);
        FormPanel[] definitions = instance.getFormDefinitions();
        assertNotNull(definitions);
        assertEquals(2, definitions.length);

        // From cache
        definitions = instance.getFormDefinitions();
        assertNotNull(definitions);
        assertEquals(2, definitions.length);
    }
}
