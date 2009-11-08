/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.client.metadata;

import com.sinco.util.ReaderUtil;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
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
public class SwingUIGeneratorTest {

    public SwingUIGeneratorTest() {
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
     * Test of processForms method, of class SwingUIGenerator.
     */
    @Test
    public void testProcessForms() {
        try {
            System.out.println("processForms");
            HashMap<String, byte[]> forms = new HashMap<String, byte[]>();

            ReaderUtil reader = new ReaderUtil("/home/cross/workspace/jaguar2/testprocess/dist/testprocess.jar");
            com.sinco.util.ClassLoader loader = com.sinco.util.ClassLoader.getInstance();
            loader.loadJar(reader.readFully());

            List<String> resourceList = loader.getResourceList();

            for (String resource : resourceList) {
                if (resource.startsWith("/forms")) {
                    InputStream stream = loader.getResourceAsStream(resource);
                    reader = new ReaderUtil(stream);
                    byte[] definition = reader.readFully();
                    String formName = resource.substring(7, resource.length() - 4);
                    forms.put(formName, definition);
                }
            }

            SwingUIGenerator instance = new SwingUIGenerator(System.getProperty("java.io.tmpdir"));
            instance.processForms(forms);
        } catch (Exception ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }
}