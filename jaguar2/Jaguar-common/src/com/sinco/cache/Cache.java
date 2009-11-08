/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.cache;

import java.util.HashMap;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 *
 * @author cross
 */
public class Cache {
    HashMap<String, CacheGroup> groups = new HashMap<String, CacheGroup>();
    
    ReentrantReadWriteLock reentranceLock = new ReentrantReadWriteLock();
    
    public CacheGroup get(String key) {
        CacheGroup group = groups.get(key);
        if (group == null) {
            reentranceLock.writeLock().lock();
            group = new CacheGroup();
            groups.put(key, group);
            reentranceLock.writeLock().unlock();
        }
        return group;
    }
}
