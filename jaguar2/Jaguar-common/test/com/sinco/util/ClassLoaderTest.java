/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.util;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class ClassLoaderTest extends TestCase {

    public ClassLoaderTest(String testName) {
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
     * Test of loadClass method, of class ClassLoader.
     */
    public void testLoadClass() {
        try {
            System.out.println("loadClass");
            InputStream is = getClass().getResourceAsStream("/com/sinco/util/TestClass.class");
            byte[] bytes = new ReaderUtil(is).readFully();
            ClassLoader instance = new ClassLoader();
            Class result = instance.loadClass(bytes);
            assertEquals("com.sinco.util.TestClass", result.getName());
        } catch (IOException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    /**
     * Test of loadDir method, of class ClassLoader.
     */
    public void testLoadDir_String() {
        System.out.println("loadDir");
        String dir = "/home/cross/workspace/jaguar2/Jaguar-common/build/classes";
        ClassLoader instance = new ClassLoader();
        instance.loadDir(dir);
    }

    /**
     * Test of loadDir method, of class ClassLoader.
     */
    public void testLoadDir_File() {
        System.out.println("loadDir");
        String sdir = "/home/cross/workspace/jaguar2/Jaguar-common/build/classes";
        File dir = new File(sdir);
        ClassLoader instance = new ClassLoader();
        instance.loadDir(dir);
    }

    public void testLoadJar() {
        try {
            System.out.println("loadJar");

            String sjar = "/home/cross/workspace/jaguar2/jaguar-data/dist/jaguar-data.jar";

            ReaderUtil reader = new ReaderUtil(sjar);

            ClassLoader instance = new ClassLoader();
            instance.loadJar(reader.readFully());
        } catch (IOException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    public void testLoadJarWithResources() {
        try {
            System.out.println("loadJarWithResources");

            String sjar = "/home/cross/workspace/jaguar2/testprocess/dist/testprocess.jar";

            ReaderUtil reader = new ReaderUtil(sjar);

            ClassLoader instance = new ClassLoader();
            instance.loadJar(reader.readFully());
        } catch (IOException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    public void testFindClassesAssignableTo() {
        try {
            System.out.println("findClassesAssignableTo");

            String sjar = "/home/cross/workspace/jaguar2/jaguar-data/dist/jaguar-data.jar";

            ReaderUtil reader = new ReaderUtil(sjar);

            ClassLoader instance = new ClassLoader();
            instance.loadJar(reader.readFully());

            Class entityClass = instance.loadClass("com.sinco.persistence.EntityManager");
            Class[] result = instance.findClassesAssignableTo(entityClass);
            assertTrue(result.length > 0);

        } catch (Exception ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }

    }

    public void testGetResourceAsStream() {
        try {
            System.out.println("getResourceAsStream");

            String sjar = "/home/cross/workspace/jaguar2/testprocess/dist/testprocess.jar";

            ReaderUtil reader = new ReaderUtil(sjar);

            ClassLoader instance = new ClassLoader();
            instance.loadJar(reader.readFully());
            
            InputStream is = instance.getResourceAsStream("/processdefinition.xml");
            assertNotNull(is);
            is.close();
        } catch (Exception ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }

    }
    
    public void testGetResourceList() {
        try {
            System.out.println("getResourceList");
            
            String sjar = "/home/cross/workspace/jaguar2/testprocess/dist/testprocess.jar";

            ReaderUtil reader = new ReaderUtil(sjar);

            ClassLoader instance = new ClassLoader();
            instance.loadJar(reader.readFully());
            
            List<String> resources =instance.getResourceList();
            
            assertTrue(resources.size() > 0);
            assertTrue(resources.contains("/processdefinition.xml"));
        } catch (Exception ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }
}
