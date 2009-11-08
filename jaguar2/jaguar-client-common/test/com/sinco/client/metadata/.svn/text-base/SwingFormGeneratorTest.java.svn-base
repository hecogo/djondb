/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client.metadata;

import com.sinco.util.ReaderUtil;
import java.io.IOException;
import java.io.InputStream;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author cross
 */
public class SwingFormGeneratorTest {

    public SwingFormGeneratorTest() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }

    @Before
    public void setUp() {
    }

    @After
    public void tearDown() {
    }

    /**
     * Test of generate method, of class SwingFormGenerator.
     */
    @Test
    public void testGenerate() {
        try {
            System.out.println("generate");

            ReaderUtil reader = new ReaderUtil("/home/cross/workspace/jaguar2/testprocess/dist/testprocess.jar");
            com.sinco.util.ClassLoader loader = com.sinco.util.ClassLoader.getInstance();
            loader.loadJar(reader.readFully());

            InputStream formIS = loader.getResourceAsStream("/forms/Form1.xml");
            reader = new ReaderUtil(formIS);
            byte[] definition = reader.readFully();
            SwingFormGenerator instance = new SwingFormGenerator("TestForm", definition);
            String sourceDestDir = System.getProperty("java.io.tmpdir");
            instance.generate(sourceDestDir);
        } catch (IOException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

}