/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.client.controls;

import com.sinco.client.controls.TextField;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
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
public class TextFieldTest {

    public TextFieldTest() {
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
     * Test of hasValue method, of class TextField.
     */
    @Test
    public void testHasValue() {
        System.out.println("hasValue");
        TextField instance = new TextField();
        boolean expResult = false;
        boolean result = instance.hasValue();
        assertEquals(expResult, result);

        instance.setValue("Test Value");
        Object objExpResult = "Test Value";
        Object value = instance.getValue();
        assertEquals(objExpResult, value);

        expResult = true;
        assertEquals(expResult, instance.hasValue());
    }

    public void testGraphics() {
        try {
            System.out.println("Graphics");

            final JFrame frm = new JFrame();
            frm.setLayout(new GridBagLayout());
            TextField instance1 = new TextField();
            GridBagConstraints c = new GridBagConstraints();
            c.insets = new Insets(5, 5, 4, 4);
            c.gridwidth = GridBagConstraints.REMAINDER;
            c.fill = GridBagConstraints.HORIZONTAL;
            frm.getContentPane().add(instance1, c);
            c.insets = new Insets(0, 0, 4, 4);
            TextField instance2 = new TextField();
            frm.getContentPane().add(instance2, c);
            TextField instance3 = new TextField();
            frm.getContentPane().add(instance3, c);
            frm.pack();
            frm.setVisible(true);
            
            while (true) {
                Thread.sleep(1000);
            }
        } catch (Exception ex) {
            Logger.getLogger(TextFieldTest.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}