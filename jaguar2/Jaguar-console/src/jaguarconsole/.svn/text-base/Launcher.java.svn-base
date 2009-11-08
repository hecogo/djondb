/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package jaguarconsole;

import com.sinco.network.NetworkService;
import java.io.IOException;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class Launcher {
    private static Log logger = LogFactory.getLog(Launcher.class);
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            if (logger.isInfoEnabled()) {
                String classpath = System.getProperty("java.class.path");
                logger.info("Classpath: " + classpath);
            }
            com.sinco.util.ClassLoader loader = com.sinco.util.ClassLoader.getInstance();
            
            NetworkService service = (NetworkService) loader.loadClass("com.sinco.network.NetworkService").newInstance();
//            NetworkService service = new NetworkService();
            service.start();

            System.in.read();

            service.stop();
        } catch (ClassNotFoundException ex) {
            logger.error(ex.getMessage(), ex);
        } catch (InstantiationException ex) {
            logger.error(ex.getMessage(), ex);
        } catch (IllegalAccessException ex) {
            logger.error(ex.getMessage(), ex);
        } catch (IOException ex) {
            logger.error(ex.getMessage(), ex);
        }
    }

}
