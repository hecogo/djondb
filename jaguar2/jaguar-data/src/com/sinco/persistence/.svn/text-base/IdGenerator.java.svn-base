/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.persistence;

import java.util.HashMap;

/**
 *
 * @author cross
 */
public class IdGenerator {

    private static HashMap<String, Key> keys;
    private static final int DEFAULTMAX = 50;
    

    static {
        keys = new HashMap<String, Key>();
    }

    public static int getNextId(String generatorName) {
        Key key = keys.get(generatorName);
        if (key == null) {
            synchronized(keys) {
                key = new Key(0, 0, DEFAULTMAX);
                keys.put(generatorName, key);
            }
        }
        return key.getNext();
    }

    private static class Key {

        int current;
        int max;
        int startId;

        public Key(int startId, int current, int max) {
            this.startId = startId;
            this.current = current;
            this.max = max;
        }
        
        public int getNext() {
            synchronized (this) {
                if (current < max) {
                    current++;
                } else {
                    startId += max;
                    current = 0;
                }
            }
            return startId + current;
        }
    }
}
