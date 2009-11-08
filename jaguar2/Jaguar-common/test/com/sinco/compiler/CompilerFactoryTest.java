/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.compiler;

import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class CompilerFactoryTest extends TestCase {
    
    public CompilerFactoryTest(String testName) {
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
     * Test of getCompiler method, of class CompilerFactory.
     */
    public void testGetCompiler() {
        System.out.println("getCompiler");
        AbstractCompiler result = CompilerFactory.getCompiler();
        assertEquals(DefaultCompiler.class, result.getClass());
    }

}
