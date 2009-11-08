/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.render.metadata;

import com.sinco.client.metadata.Form;
import com.sinco.client.metadata.DigesterUtil;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
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
    public void testProcessXML_InputStream() {
        System.out.println("processXML");
        InputStream xml = getClass().getResourceAsStream("/forms/Form1.xml");
        DigesterUtil instance = new DigesterUtil();
        Form result = instance.processXML(xml);
        testForm(result);
        
    }

    /**
     * Test of processXML method, of class DigesterUtil.
     */
    public void testProcessXML_File() {
        System.out.println("processXML");
        final String file = System.getProperty("java.io.tmpdir") + "/test.xml";
        createTmpFile(file);
        DigesterUtil instance = new DigesterUtil();
        Form result = instance.processXML(new File(file));

        testForm(result);
    }

    /**
     * Test of processXML method, of class DigesterUtil.
     */
    public void testProcessXML_String() {
        System.out.println("processXML");
        String path = System.getProperty("java.io.tmpdir") + "/test.xml";
        createTmpFile(path);
        DigesterUtil instance = new DigesterUtil();
        Form result = instance.processXML(path);
        
        testForm(result);
    }

    private void createTmpFile(final String file) {
        try {
            FileOutputStream fos = new FileOutputStream(file);
            InputStream xmlIS = getClass().getResourceAsStream("/forms/Form1.xml");
            byte[] buf = new byte[1024];
            int readed;
            while ((readed = xmlIS.read(buf)) > 0) {
                fos.write(buf, 0, readed);
            }
            fos.flush();
            fos.close();
        } catch (IOException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    private void testForm(Form result) {
        assertNotNull(result);
        assertEquals("${resources.form1Description}", result.getDescription());
        assertEquals(1, result.getId());
        assertEquals(2, result.getFields().size());
    }

}
