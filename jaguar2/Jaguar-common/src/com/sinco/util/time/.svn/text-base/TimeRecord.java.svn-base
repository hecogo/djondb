/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.util.time;

import java.util.Calendar;

/**
 *
 * @author cross
 */
public class TimeRecord {
    private long start;
    
    private TimeRecord() {
        start = Calendar.getInstance().getTimeInMillis();
    }
    
    public static TimeRecord getTimeRecord() {
        TimeRecord record = new TimeRecord();
        return record;
    }
    
    public long getTimeInMillis() {
        long end = Calendar.getInstance().getTimeInMillis();
        return end - start;
    }
}
