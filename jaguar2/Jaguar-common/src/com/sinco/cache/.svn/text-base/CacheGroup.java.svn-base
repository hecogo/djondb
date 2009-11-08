/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.cache;

import java.util.HashMap;

/**
 *
 * @author cross
 */
public class CacheGroup {
    HashMap<String, CacheItem> items = new HashMap<String, CacheItem>();
    
    public void add(String key, Object value) {
        CacheItem item = new CacheItem();
        item.setKey(key);
        item.setValue(value);
        
        items.put(key, item);
    }
    
    public Object get(String key) {
        CacheItem item = items.get(key);
        if (item == null) {
            return null;
        } else {
            item.updateLastTimeUsed();
            return item.getValue();
        }
    }

    public void remove(String key) {
        items.remove(key);
    }
}
