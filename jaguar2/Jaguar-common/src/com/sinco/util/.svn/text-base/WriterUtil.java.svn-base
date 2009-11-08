/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.util;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

/**
 *
 * @author cross
 */
public class WriterUtil {
    private OutputStream stream;
    
    public WriterUtil(OutputStream stream) {
        this.stream = stream;
    }
    
    public WriterUtil(FileOutputStream file) {
        this.stream = file;
    }
    
    public WriterUtil(String filepath) throws FileNotFoundException {
        this.stream = new FileOutputStream(filepath);
    }

    public void close() throws IOException {
        this.stream.close();
    }

    public void write(String text) throws IOException {
        stream.write(text.getBytes());
    }
}
