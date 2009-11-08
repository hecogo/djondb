/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.cache;

import java.util.ArrayList;
import java.util.Random;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class AllCacheTest extends TestCase {
    
    public AllCacheTest(String testName) {
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

    public void testGlobalCache() {
        String value = "valor";
        CacheFactory.getGlobalCache("GROUP1").add("test", value);
        
        String expectedValue = "valor";
        Object result = CacheFactory.getGlobalCache("GROUP1").get("test");
        assertEquals(expectedValue, result);
    }
    
    public void testRuntimeCache() {
        try {
            
            Runnable runnable = new Runnable() {

                public void run() {
                    try {
                        System.out.println(String.format("Starting: %d" , Thread.currentThread().getId()));
                        int valor = new Random(Thread.currentThread().getId()).nextInt();
                        CacheFactory.getRuntimeCache().add("VALUE", valor);
                        Thread.sleep(1000);
                        int nuevoValor = ((Integer)CacheFactory.getRuntimeCache().get("VALUE")).intValue();
                        
                        assertEquals(valor, nuevoValor);

                        valor = new Random(Thread.currentThread().getId()).nextInt();
                        CacheFactory.getRuntimeCache().add("VALUE2", valor);
                        Thread.sleep(1000);
                        nuevoValor = ((Integer)CacheFactory.getRuntimeCache().get("VALUE2")).intValue();
                        
                        assertEquals(valor, nuevoValor);
                        System.out.println(String.format("End: %d" , Thread.currentThread().getId()));
                    } catch (InterruptedException ex) {
                    }
                }
            };
            // This first test will try to execute without thread in order to test if one
            // instance is running as expected.
            runnable.run();
            ArrayList<Thread> threads = new ArrayList<Thread>();
            for (int x = 0; x < 10; x++) {
                Thread thread1 = new Thread(runnable);
                thread1.start();
                threads.add(thread1);
                //thread1.join();
            }
            for (Thread thread : threads) {
                thread.join();
            }
        } catch (InterruptedException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
        
    }
}
