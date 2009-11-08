/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.util;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

/**
 *
 * @author cross
 */
public class ReaderUtil {
    private InputStream stream;
    
    public ReaderUtil(InputStream stream) {
        this.stream = stream;
    }
    
    public ReaderUtil(FileInputStream file) {
        this.stream = file;
    }
    
    public ReaderUtil(String filepath) throws FileNotFoundException {
        this.stream = new FileInputStream(filepath);
    }
    
    public byte[] readFully() throws IOException {
        byte[] buffer = new byte[1024];
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        int readed;
        while ((readed = stream.read(buffer, 0, 1024)) > -1) {
            baos.write(buffer, 0, readed);
        }
        baos.flush();
        baos.close();

        return baos.toByteArray();
    }
}
