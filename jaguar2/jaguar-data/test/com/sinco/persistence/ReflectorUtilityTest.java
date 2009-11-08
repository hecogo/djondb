/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.persistence;

import java.beans.PropertyDescriptor;
import java.lang.reflect.Field;
import java.util.Arrays;
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
public class ReflectorUtilityTest {

    public ReflectorUtilityTest() {
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
     * Test of getPrimaryKeyDescriptor method, of class ReflectorUtility.
     */
    @Test
    public void testGetPrimaryKeyDescriptor() {
        System.out.println("getPrimaryKeyDescriptor");
        TestEntity entity = new TestEntity();

        ReflectorUtility instance = new ReflectorUtility();
        PropertyDescriptor result = instance.getPrimaryKeyDescriptor(entity);
        assertNotNull(result);
        
    }

    /**
     * Test of getPrimaryKey method, of class ReflectorUtility.
     */
    @Test
    public void testGetPrimaryKey() {
        System.out.println("getPrimaryKey");
        TestEntity entity = new TestEntity();
        entity.setId(1);
        ReflectorUtility instance = new ReflectorUtility();
        int expResult = 1;
        Object result = instance.getPrimaryKey(entity);
        assertEquals(expResult, result);
    }

    /**
     * Test of getFields method, of class ReflectorUtility.
     */
    @Test
    public void testGetFields() {
        System.out.println("getFields");
        TestEntity entity = new TestEntity();
        ReflectorUtility instance = new ReflectorUtility();
        Field[] result = instance.getFields(entity, true);
        
        assertEquals(3, result.length);
        for (Field field : result) {
            assertTrue("id,name,childEntities,".contains(field.getName()));
        }
        
        System.out.println("Testing inheritance");
        InheritedEntity inh = new InheritedEntity();
        inh.setId(10);
        inh.setName("Name");
        
        result = instance.getFields(inh, true);
        assertEquals(3, result.length);
        
        for (Field field : result) {
            assertTrue("id,name,integerValue,".contains(field.getName()));
        }
    }

}