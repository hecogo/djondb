/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.util;

/**
 *
 * @author cross
 */
public class ClassLoader extends java.lang.ClassLoader {

    public ClassLoader() {
        super();
    }

    public ClassLoader(java.lang.ClassLoader parent) {
        super(parent);
    }

    public Class<?> loadFromBytes(String className, byte[] bytes) {
        Class<?> clazz = this.defineClass(className, bytes, 0, bytes.length);
        return clazz;
    }
}
