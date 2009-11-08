/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.persistence;

import java.util.ArrayList;
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
public class HashEntityManagerTest {

    public HashEntityManagerTest() {
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
     * Test of createNamedQuery method, of class HashEntityManager.
     */
    @Test
    public void testCreateNamedQuery() {
        System.out.println("createNamedQuery");
        fail("The test case is a prototype.");
    }

    /**
     * Test of createQuery method, of class HashEntityManager.
     */
    @Test
    public void testCreateQuery() {
        System.out.println("createQuery");
        fail("The test case is a prototype.");
    }

    /**
     * Test of find method, of class HashEntityManager.
     */
    @Test
    public void testFind() {
        try {
            System.out.println("find");

            TestEntity entity = new TestEntity();
            entity.setName("MyName");

            HashEntityManager manager = new HashEntityManager();
            entity = manager.persist(entity);

            System.out.println("Recovering from cache");
            TestEntity found = manager.find(TestEntity.class, entity.getId());
            assertEquals(found.getName(), entity.getName());
            
            TestEntity withCollections = new TestEntity();
            withCollections.setMitransient(2);
            withCollections.setName("Other name");
            TestChildEntity child = new TestChildEntity();
            child.setChildName("childName");
            child.setParentEntity(withCollections);
            ArrayList<TestChildEntity> childs = new ArrayList<TestChildEntity>();
            childs.add(child);
            child = new TestChildEntity();
            child.setChildName("childName2");
            child.setParentEntity(withCollections);
            childs.add(child);
            withCollections.setChildEntities(childs);
            TestEntity persistedWithChilds = manager.persist(withCollections);
            found = manager.find(TestEntity.class, persistedWithChilds.getId());
            assertNotNull(found);
            assertNotNull(found.getChildEntities());
            assertEquals(withCollections.getChildEntities().size(), found.getChildEntities().size());
            
            System.out.println("Recovering from reposity");
            manager = new HashEntityManager();
            found = manager.find(TestEntity.class, entity.getId());
            assertEquals(found.getName(), entity.getName());

            found = manager.find(TestEntity.class, persistedWithChilds.getId());
            assertNotNull(found);
            assertNotNull(found.getChildEntities());
            assertEquals(withCollections.getChildEntities().size(), found.getChildEntities().size());
        } catch (EntityNotFoundException ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
        
    }

    /**
     * Test of persist method, of class HashEntityManager.
     */
    @Test
    public void testPersist() {
        System.out.println("persist");
        TestEntity entity = new TestEntity();
        entity.setName("test");

        HashEntityManager manager = new HashEntityManager();
        entity = manager.persist(entity);
        System.out.println(String.format("Persisted with id: %d", entity.getId()));
    }

    /**
     * Test of merge method, of class HashEntityManager.
     */
    @Test
    public void testMerge() {
        System.out.println("merge");
        fail("The test case is a prototype.");
    }

    /**
     * Test of remove method, of class HashEntityManager.
     */
    @Test
    public void testRemove() {
        System.out.println("remove");
        fail("The test case is a prototype.");
    }
}