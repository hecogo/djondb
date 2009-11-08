/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network.plugin;

import com.sinco.network.plugin.converters.ConverterFactory;

/**
 *
 * @author cross
 */
public class Attribute {
    private Class type;
    private Converter converter;

    public Class getType() {
        return type;
    }

    public void setType(Class type) {
        this.type = type;
    }

    public Converter getConverter() {
        if (converter == null) {
            converter = ConverterFactory.getConverter(getType());
        }
        return converter;
    }

    public void setConverter(Converter converter) {
        this.converter = converter;
    }
    
    
}
