/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.cache;

import java.util.Calendar;
import java.util.HashMap;

/**
 *
 * @author cross
 */
class CacheItem {
    private long lastTimeUsed;
    private String key;
    private Object value;

    void updateLastTimeUsed() {
        lastTimeUsed = Calendar.getInstance().getTimeInMillis();
    }

    long getLastTimeUsed() {
        return lastTimeUsed;
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public Object getValue() {
        return value;
    }

    public void setValue(Object value) {
        this.value = value;
    }
    
}
