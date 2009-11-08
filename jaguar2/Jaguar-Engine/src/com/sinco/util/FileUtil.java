/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.util;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 *
 * @author cross
 */
public class FileUtil {

    public byte[] readFile(InputStream stream) throws IOException {
        byte[] buffer = new byte[1024];
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        int len;
        while ((len = stream.read(buffer)) > 0) {
            out.write(buffer, 0, len);
        }
        out.flush();
        out.close();
        stream.close();
        return out.toByteArray();
    }
    
    public byte[] readFile(File file) throws IOException {
        FileInputStream stream = new FileInputStream(file);
        return readFile(stream);
    }
    
    public byte[] readFile(String path) throws IOException {
        return readFile(new File(path));
    }
}
