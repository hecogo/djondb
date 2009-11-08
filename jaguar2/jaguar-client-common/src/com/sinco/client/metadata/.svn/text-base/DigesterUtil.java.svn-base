/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client.metadata;

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

    public Form processXML(InputStream xml) {
        try {
            Digester digester = new Digester();

            digester.addObjectCreate("*/form", "com.sinco.client.metadata.Form");
            digester.addObjectCreate("*/field", "com.sinco.client.metadata.Field");
            
            digester.addSetProperties("*/form");
            digester.addSetNext("*/field", "addField");
            digester.addSetProperties("*/field");

            Form form = (Form) digester.parse(xml);
            return form;
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        } catch (SAXException ex) {
            throw new RuntimeException(ex);
        }
    }

    public Form processXML(File file) {
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

    public Form processXML(String path) {
        File file = new File(path);
        return processXML(file);
    }
}
