/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.network;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class RequestSocketTest extends TestCase {

    public RequestSocketTest(String testName) {
        super(testName);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    /**
     * Test of run method, of class RequestSocket.
     */
    public void testSendingData() {
        try {
            System.out.println("sendingData");

            Socket client = new Socket(InetAddress.getLocalHost(), 1043);
            OutputStream outputStream = client.getOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(outputStream);
            
            String testData = "asdf";

            outputStream.write(testData.getBytes());
            outputStream.flush();

            InputStream is = client.getInputStream();

            byte[] buffer = new byte[1024];
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            int readed;
            while ((readed = is.read(buffer))> -1) {
                baos.write(buffer, 0, readed);
            }
            baos.flush();
            System.out.println("Bytes readed: " + baos.toByteArray());
            
            System.out.println("Readed: " + new String(baos.toByteArray()));

            ByteArrayInputStream bais = new ByteArrayInputStream(baos.toByteArray());
            ObjectInputStream ois = new ObjectInputStream(bais);
            Object obj = ois.readObject();
            System.out.println("Received : " + obj);
            bais.close();
            oos.close();
            outputStream.close();
            is.close();

            client.close();
        } catch (Exception ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }
}
