/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.util;

import java.rmi.server.UID;
import java.util.Calendar;
import java.util.Hashtable;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class StringUtilTest extends TestCase {

    public StringUtilTest(String testName) {
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
     * Test of replaceAll method, of class StringUtil.
     */
    public void testReplaceAll() {
        System.out.println("replaceAll");

        String text = "abcdefabcdef";
        String replace = "cd";
        String replaceWith = "xx";
        String expected = "abxxefabxxef";
        String result = StringUtil.replaceAll(text, replace, replaceWith);
        assertEquals(expected, result);

        text = "abcdefabcdef";
        replace = "cd";
        replaceWith = "xxxx";
        expected = "abxxxxefabxxxxef";
        result = StringUtil.replaceAll(text, replace, replaceWith);
        assertEquals(expected, result);

        text = "abcdefabcdef";
        replace = "cd";
        replaceWith = "x";
        expected = "abxefabxef";
        result = StringUtil.replaceAll(text, replace, replaceWith);
        assertEquals(expected, result);

        text = "abcdefabcdef";
        replace = "cdef";
        replaceWith = "cdefcdef";
        expected = "abcdefcdefabcdefcdef";
        result = StringUtil.replaceAll(text, replace, replaceWith);
        assertEquals(expected, result);
    }

    /**
     * Test of indexOf method, of class StringUtil.
     */
    public void testPerformance() {
        System.out.println("performance");
        String text = "";
        for (int x = 1; x < 255; x++) {
            text += String.valueOf((char) x);
        }
        String find = "mno";

        int timerId = startClock();
        for (int x = 0; x < 10000; x++) {
            StringUtil.replaceAll(text, find, "onm");
        }
        long timeWithNew = stopClock(timerId);

        timerId = startClock();
        for (int x = 0; x < 10000; x++) {
            text.replaceAll(find, "onm");
        }
        long timeWithJava = stopClock(timerId);

        System.out.println("My Time: " + timeWithNew);
        System.out.println("Java time: " + timeWithJava);

        assertTrue(timeWithJava > timeWithNew);
    }
    
    
    Hashtable<Integer, Long> timers = new Hashtable<Integer, Long>();

    private int startClock() {
        int uid = new UID().hashCode();

        long startTime = Calendar.getInstance().getTimeInMillis();
        timers.put(uid, startTime);
        return uid;
    }

    private long stopClock(int uid) {
        long endTime = Calendar.getInstance().getTimeInMillis();
        long startTime = timers.get(uid);
        timers.remove(uid);
        return endTime - startTime;
    }
}
