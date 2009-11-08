/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.network;

import com.sinco.cache.CacheFactory;
import com.sinco.cache.CacheGroup;
import com.sinco.network.plugin.Attribute;
import com.sinco.network.plugin.JaguarPluginDefinition;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class RequestSocket implements Runnable {

    private static Log logger = LogFactory.getLog(RequestSocket.class);
    private Socket incomming;

    public RequestSocket(Socket incomming) {
        this.incomming = incomming;
    }

    public void run() {
        OutputStream outputStream = null;
        InputStream inputStream = null;
        ObjectInputStream ois = null;
        ObjectOutputStream oos = null;
        try {
            if (logger.isDebugEnabled()) {
                logger.debug("Receiving request");
            }
            outputStream = incomming.getOutputStream();
            inputStream = incomming.getInputStream();

            ois = new ObjectInputStream(inputStream);
            oos = new ObjectOutputStream(outputStream);

            if (logger.isDebugEnabled()) {
                logger.debug("Reading socket request");
            }
            Long requestType = ois.readLong();

            RequestProcessor processor = new RequestProcessor();
            Object responses[] = processor.processRequest(requestType, ois);
            
            oos.writeInt(responses.length);
            for (Object response : responses) {
                oos.writeObject(response);
            }
            oos.flush();
            int x = 0;
            while (incomming.isConnected()) {
                Thread.sleep(100);
                x++;
                if (x == 10) {
                    break;
                }
            }
        } catch (IOException ex) {
            logger.error(ex);
        } catch (InterruptedException ex) {
            logger.error(ex);
        } finally {
            try {
                if (ois != null) {
                    ois.close();
                }
                if (oos != null) {
                    oos.close();
                }
                if (outputStream != null) {
                    outputStream.close();
                }
                if (incomming != null) {
                    incomming.close();
                }
            } catch (Exception e) {
            }
        }
    }

    private void validateRequest(Object request) throws InvalidRequestException {
        if (request == null) {
            throw new InvalidRequestException("The request cannot be null");
        }
    }
}
