/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network.config;

import java.io.IOException;
import java.io.InputStream;
import org.apache.commons.digester.Digester;
import org.xml.sax.SAXException;

/**
 *
 * @author cross
 */
public class Configuration {

    public Jaguar processXML(InputStream xml) {
        try {
            Digester digester = new Digester();

            digester.addObjectCreate("jaguar", "com.sinco.network.config.Jaguar");
            digester.addObjectCreate("*/controller", "com.sinco.network.config.Controller");
            digester.addBeanPropertySetter("*/controller/controller-class", "controllerClass");
            digester.addBeanPropertySetter("*/controller/request-class", "requestClass");
            digester.addBeanPropertySetter("*/controller/response-class", "responseClass");
            digester.addBeanPropertySetter("*/controller/name", "name");
            digester.addBeanPropertySetter("*/controller/description", "description");
            
            digester.addSetProperties("process");
            digester.addSetProperties("*/controller");
            digester.addSetNext("*/controller", "addController");

            Jaguar configuration = (Jaguar) digester.parse(xml);
            return configuration;
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        } catch (SAXException ex) {
            throw new RuntimeException(ex);
        }
    }
}
