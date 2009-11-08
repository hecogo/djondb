/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.metadata.deployment;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import org.apache.commons.digester.Digester;
import org.xml.sax.SAXException;

/**
 *
 * @author cross
 */
public class DigesterUtil {

    public Process processXML(InputStream xml) {
        try {
            Digester digester = new Digester();

            digester.addObjectCreate("process", "com.sinco.bpm.metadata.deployment.Process");
            digester.addObjectCreate("*/event", "com.sinco.bpm.metadata.deployment.Event");
            digester.addObjectCreate("*/sequenceflow", "com.sinco.bpm.metadata.deployment.SequenceFlow");
            digester.addObjectCreate("*/target", "com.sinco.bpm.metadata.deployment.Target");
            digester.addObjectCreate("*/task", "com.sinco.bpm.metadata.deployment.Task");
            
            digester.addSetProperties("process");
            digester.addSetProperties("*/event");
            digester.addSetNext("*/event", "addEvent");//, "com.sinco.bpm.metadata.deployment.Event");
            digester.addSetProperties("*/sequenceflow");
            digester.addSetNext("*/sequenceflow", "addSequenceFlow");//, "com.sinco.bpm.metadata.deployment.Event");
            digester.addSetProperties("*/target");
            digester.addSetNext("*/target", "addTarget");//, "com.sinco.bpm.metadata.deployment.Event");
            digester.addSetProperties("*/task");
            digester.addSetNext("*/task", "addTask");//, "com.sinco.bpm.metadata.deployment.Event");

            Process process = (Process) digester.parse(xml);
            return process;
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        } catch (SAXException ex) {
            throw new RuntimeException(ex);
        }
    }

    public Process processXML(File file) {
        FileInputStream in = null;
        try {
            in = new FileInputStream(file);
            return processXML(in);
        } catch (FileNotFoundException ex) {
            throw new RuntimeException(ex);
        } finally {
            try {
                in.close();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        }
    }

    public Process processXML(String path) {
        File file = new File(path);
        return processXML(file);
    }
}
