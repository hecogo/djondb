/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network;

import java.util.logging.Level;
import java.util.logging.Logger;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class NetworkServiceTest extends TestCase {

    private static NetworkService instance;
    
    public NetworkServiceTest(String testName) {
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
     * Test of start method, of class NetworkService.
     */
    public void testStart() {
        System.out.println("start");
        instance = new NetworkService();
        instance.start();
    }

    /**
     * Test of stop method, of class NetworkService.
     */
    public void testStop() {
        System.out.println("stop");
        instance.stop();
    }

}
