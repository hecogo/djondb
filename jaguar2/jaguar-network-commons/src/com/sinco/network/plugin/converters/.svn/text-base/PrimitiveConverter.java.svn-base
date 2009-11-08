/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.network.plugin.converters;

import com.sinco.network.plugin.Converter;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author cross
 */
public class PrimitiveConverter implements Converter {

    enum Primitive {

        INTEGER,
        DOUBLE,
        STRING,
        DATE
    }
    private Primitive type;

    PrimitiveConverter(Primitive type) {
        this.type = type;
    }

    public Object getValue(byte[] bytes) throws IOException {
        ObjectInputStream ois = null;
        ByteArrayInputStream bais = new ByteArrayInputStream(bytes);
        ois = new ObjectInputStream(bais);
        Object result = readValue(ois);
        ois.close();
        bais.close();
        return result;
    }

    public byte[] getBytes(Object obj) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    private Object readValue(ObjectInputStream ois) throws IOException {
        try {
            switch (type) {
                case INTEGER:
                    return ois.readInt();
                case DOUBLE:
                    return ois.readDouble();
                case STRING:
                    return ois.readObject().toString();
                case DATE:
                    return (Date) ois.readObject();
                default:
                    throw new IllegalArgumentException();
            }
        } catch (ClassNotFoundException ex) {
            // the primitive types will be always found
            throw new RuntimeException(ex);
        }
    }
}
