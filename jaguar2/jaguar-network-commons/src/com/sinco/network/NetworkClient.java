/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.network;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class NetworkClient {

    private static final Log logger = LogFactory.getLog(NetworkClient.class);
    
    public Object[] sendReceive(String host, int port, long requestType, Object[] data) throws UnknownHostException, NetworkException {
        Socket client = null;
        try {
            if (logger.isDebugEnabled()) logger.debug(String.format("Connecting with %s:%d", host, port));
            client = new Socket(host, port);
            OutputStream outputStream = client.getOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(outputStream);

            oos.writeLong(requestType);
            for (Object item : data) {
                if (logger.isDebugEnabled()) logger.debug(String.format("Sending data: %s", item.getClass().getName()));
                oos.writeObject(item);
            }
            
            oos.flush();

            if (logger.isDebugEnabled()) logger.debug("Getting response");
            InputStream is = client.getInputStream();

            ObjectInputStream ois = new ObjectInputStream(is);
            
            int length = ois.readInt();
            Object[] result = new Object[length];
            for (int x = 0; x < length; x++) {
                result[x] = ois.readObject();
            }
            ois.close();
            is.close();
            oos.close();
            outputStream.close();
            
            return result;
/*
            byte[] buffer = new byte[1024];
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            int readed;
            while ((readed = is.read(buffer)) > -1) {
                baos.write(buffer, 0, readed);
            }
            baos.flush();
            is.close();
            
            ByteArrayInputStream bais = new ByteArrayInputStream(baos.toByteArray());
            ObjectInputStream ois = new ObjectInputStream(bais);
            int length = ois.readInt();
            Object[] result = new Object[length];
            for (int x = 0; x < length; x++) {
                result[x] = ois.readObject();
            }
            bais.close();
 */
        } catch (IOException ex) {
            throw new NetworkException(ex);
        } catch (ClassNotFoundException ex) {
            throw new NetworkException(ex);
        } finally {
            if ((client != null) && (client.isConnected())) {
                try {
                    client.close();
                } catch (IOException ex) {
                }
            }
        }
    }
}
