/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.util;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.jar.JarInputStream;
import java.util.zip.ZipEntry;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class ClassLoader extends java.lang.ClassLoader {

    private static Log logger = LogFactory.getLog(ClassLoader.class);
    private ArrayList<Class> loadedClasses;
    private static ClassLoader instance;
    private HashMap<String, byte[]> loadedResources;

    public ClassLoader() {
        initialize();
    }

    private void initialize() {
        loadedClasses = new ArrayList<Class>();
        loadedResources = new HashMap<String, byte[]>();
    }

    public Class loadClass(byte[] bytes) {
        if (logger.isDebugEnabled()) {
            logger.debug("loading class from bytes");
        }
        Class newClass = this.defineClass(null, bytes, 0, bytes.length);

        resolveClass(newClass);

        loadedClasses.add(newClass);

        if (logger.isDebugEnabled()) {
            logger.debug(String.format("Class %s resolved", newClass.getName()));
        }
        return newClass;
    }

    public Class[] loadDir(String dir) {
        return loadDir(new File(dir));
    }

    public Class[] loadDir(File dir) {
        if (!dir.isDirectory()) {
            throw new IllegalArgumentException(String.format("%s is not a directory", dir.getName()));
        }

        if (logger.isDebugEnabled()) {
            logger.debug(String.format("Loading classes in dir: %s", dir));
        }
        ArrayList<Class> classes = new ArrayList<Class>();
        File[] files = dir.listFiles();
        for (File file : files) {
            try {
                if (file.isDirectory()) {
                    Class[] dirClasses = loadDir(file);
                    List lstClasses = Arrays.asList(dirClasses);
                    classes.addAll(lstClasses);
                    continue;
                }

                ReaderUtil reader = new ReaderUtil(new FileInputStream(file));
                byte[] bytes = reader.readFully();

                classes.add(loadClass(bytes));
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        }
        return classes.toArray(new Class[]{});
    }

    public Class[] loadJar(byte[] jar) {
        if (logger.isDebugEnabled()) {
            logger.debug("Loading jar");
        }
        ArrayList<Class> classes = new ArrayList<Class>();
        JarInputStream jis = null;
        try {
            jis = new JarInputStream(new ByteArrayInputStream(jar));
            ZipEntry entry;
            ArrayList<byte[]> classesToLoad = new ArrayList<byte[]>();
            while ((entry = jis.getNextEntry()) != null) {
                ByteArrayOutputStream baos = new ByteArrayOutputStream();

                if (logger.isDebugEnabled()) {
                    logger.debug(String.format("Entry found: %s", entry.getName()));
                }
                byte[] file = new ReaderUtil(jis).readFully();
                if (!entry.isDirectory()) {
                    if (entry.getName().endsWith(".class")) {
                        classesToLoad.add(file);
                    } else {
                        loadResource(entry.getName(), file);
                    }
                }
            }
            jis.close();

            NoClassDefFoundError lastError = null;
            while (true) {
                int x = 0;
                int classesLoadedThisLoop = 0;
                int currentSize = classesToLoad.size();
                while (x < currentSize) {
                    byte[] file = classesToLoad.get(0);
                    classesToLoad.remove(0);
                    try {
                        Class clazz = loadClass(file);
                        classes.add(clazz);
                        classesLoadedThisLoop++;
                    } catch (NoClassDefFoundError e) {
                        lastError = e;
                        classesToLoad.add(file);
                    }
                    x++;
                }
                if (classesToLoad.size() == 0) {
                    break;
                }
                if (classesLoadedThisLoop == 0) {
                    throw lastError;
                }
            }
            return classes.toArray(new Class[]{});
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        } finally {
            try {
                jis.close();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        }
    }

    public Class[] findClassesAssignableTo(Class implementedInterface) {
        if (!implementedInterface.isInterface()) {
            throw new IllegalArgumentException(String.format("The class %s must be an interface", implementedInterface.getName()));
        }

        ArrayList<Class> foundClasses = new ArrayList<Class>();
        for (Class clazz : loadedClasses) {
            for (Class clazzInterface : clazz.getInterfaces()) {
                if (clazzInterface.equals(implementedInterface)) {
                    foundClasses.add(clazz);
                    continue;
                }
            }
        }
        return foundClasses.toArray(new Class[]{});
    }

    @Override
    protected URL findResource(String name) {
        return super.findResource(name);
    }

    @Override
    public InputStream getResourceAsStream(String name) {
        if (loadedResources.containsKey(name)) {
            ByteArrayInputStream bais = new ByteArrayInputStream(loadedResources.get(name));
            return bais;
        } else {
            InputStream is = null;
            if (getParent() != null) {
                is = getParent().getResourceAsStream(name);
            }
            if (is == null) {
                is = super.getResourceAsStream(name);
            }
            return is;
        }
    }

    public static ClassLoader getInstance() {
        if (instance == null) {
            instance = new com.sinco.util.ClassLoader();
        }
        return instance;
    }

    private void loadResource(String fullName, byte[] file) {
        loadedResources.put("/" + fullName, file);
    }

    /**
     * Returns the list of the loaded resources
     * @return
     */
    public List<String> getResourceList() {
        ArrayList<String> result = new ArrayList<String>(loadedResources.size());
        for (String key : loadedResources.keySet()) {
            result.add(key);
        }

        return result;
    }
}
