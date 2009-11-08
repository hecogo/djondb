/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.util;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

/**
 *
 * @author cross
 */
public class ClonerUtility {

    public Object clone(Serializable obj) {
        ObjectOutputStream oout = null;
        try {
            ByteArrayOutputStream bout = new ByteArrayOutputStream();
            oout = new ObjectOutputStream(bout);

            oout.writeObject(obj);

            oout.flush();
            oout.close();
            bout.close();

            byte[] bytes = bout.toByteArray();

            ByteArrayInputStream bin = new ByteArrayInputStream(bytes);
            ObjectInputStream oin = new ObjectInputStream(bin);
            Object result = oin.readObject();
            oin.close();
            bin.close();

            return result;
        } catch (ClassNotFoundException ex) {
            throw new RuntimeException(ex);
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        } finally {
            try {
                oout.close();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        }
    }
}
