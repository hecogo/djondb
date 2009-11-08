/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.cache;

import java.net.UnknownHostException;
import java.util.HashMap;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author cross
 */
public class CacheFactory {

    private static HashMap<String, CacheGroup> runtimeCache;
    private static Cache globalCache;
    private static ReentrantReadWriteLock reentrantRuntimeLock = new ReentrantReadWriteLock();
    
    static {
        runtimeCache = new HashMap<String, CacheGroup>();
        globalCache = new Cache();
    }
    
    public static CacheGroup getGlobalCache(String group) {
        return globalCache.get(group);
    }
    
    public static CacheGroup getRuntimeCache() {
        try {
            String hostAddress = java.net.Inet6Address.getLocalHost().getHostAddress();
            long threadId = Thread.currentThread().getId();
            String key = hostAddress + "@" + threadId;

            CacheGroup cache = runtimeCache.get(key);
            if (cache == null) {
//                reentrantRuntimeLock.writeLock().lock();
                cache = new CacheGroup();
                runtimeCache.put(key, cache);
//                reentrantRuntimeLock.writeLock().unlock();
            }
            return cache;
        } catch (UnknownHostException ex) {
            throw new RuntimeException(ex);
        }
    }
}
