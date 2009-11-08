/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.network;

import com.sinco.cache.CacheFactory;
import com.sinco.cache.CacheGroup;
import com.sinco.client.metadata.UIGenerator;
import com.sinco.client.metadata.UIGeneratorFactory;
import com.sinco.client.metadata.UIGeneratorType;
import com.sinco.network.config.Configuration;
import com.sinco.network.config.Jaguar;
import com.sinco.network.plugin.JaguarPluginDefinition;
import com.sinco.util.ClassLoader;
import com.sinco.util.ReaderUtil;
import com.sinco.util.time.TimeRecord;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class NetworkService {

    public static final String SERVICE_GLOBALKEY = "NETWORKSERVICE";
    static final String PLUGINDEFINITIONS = "PLUGINDEFINITIONS";
    private int status = 0;
    public static final int PORT = 1048;
    private static Log logger = LogFactory.getLog(NetworkService.class);
    private Thread threadService;
    private ServerSocket server;

    public NetworkService() {
    }

    public void start() {
        if (status == 1) {
            throw new IllegalStateException("The network service is already active. Try stopping it first");
        }
        TimeRecord record = TimeRecord.getTimeRecord();
        if (logger.isInfoEnabled()) {
            logger.info("Starting network service");
        }

        int warningMessages = 0;
        try {
            loadJars();
            loadConfiguration();
            initializeMapping();
            deployProject();
        } catch (NetworkServiceException ex) {
            logger.error(ex.getMessage(), ex);
            warningMessages++;
        }

        synchronized (this) {
            try {
                status = 1;
                threadService = new Thread(new Listener(this));
                threadService.start();

                wait();
            } catch (InterruptedException ex) {
                logger.error(ex.getMessage(), ex);
            }
        }
        if (warningMessages > 0) {
            if (logger.isWarnEnabled()) {
                logger.warn("The server started with warnings.");
            }
        }
        if (logger.isInfoEnabled()) {
            long end = record.getTimeInMillis();
            int mins = (int) Math.floor(((double) end / (double) 1000) / 60);
            double secs = (((double) end / (double) 1000) - (mins * 60));
            logger.info(String.format("Network service started. Time: %02d:%05.2f", mins, secs));
        }
    }

    public void stop() {
        try {
            if (status == 0) {
                throw new IllegalStateException("The network service is already inactive. Try starting it first");
            }
            if (logger.isInfoEnabled()) {
                logger.info("Stopping network service");
            }
            status = 0;
            server.close();
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    private void deployProject() {
        try {
            if (logger.isDebugEnabled()) {
                logger.debug("Starting project deployment.");
            }
            // Temporally static deployment
            ReaderUtil reader = new ReaderUtil("/home/cross/workspace/jaguar2/testprocess/dist/testprocess.jar");

            ClassLoader.getInstance().loadJar(reader.readFully());

            InputStream xml = ClassLoader.getInstance().getResourceAsStream("/processdefinition.xml");

            reader = new ReaderUtil(xml);
            byte[] processDefinition = reader.readFully();
            String xmltext = new String(processDefinition);

            RequestProcessor processor = new RequestProcessor();
            processor.processRequest(101L, new Object[] {xmltext});
            
            if (logger.isDebugEnabled()) {
                logger.debug("Project deployed.");
                logger.debug("Preparing render.");
            }
            prepareUI();
            
            if (logger.isDebugEnabled()) {
                logger.debug("Render ready.");
            }
        } catch (UnknownHostException ex) {
            logger.error("Project not deployed. Error: " + ex.getMessage(), ex);
            throw new RuntimeException("Project not deployed. Error: " + ex.getMessage());
        } catch (InvalidRequestException ex) {
            logger.error("Project not deployed. Error: " + ex.getMessage(), ex);
            throw new RuntimeException("Project not deployed. Error: " + ex.getMessage());
        } catch (FileNotFoundException ex) {
            logger.error("Project not deployed. Error: " + ex.getMessage(), ex);
            throw new RuntimeException("Project not deployed. Error: " + ex.getMessage());
        } catch (IOException ex) {
            logger.error("Project not deployed. Error: " + ex.getMessage(), ex);
            throw new RuntimeException("Project not deployed. Error: " + ex.getMessage());
        }
    }

    private List<Class> getPlugins() throws NetworkServiceException {
        Class[] plugins = com.sinco.util.ClassLoader.getInstance().findClassesAssignableTo(com.sinco.network.plugin.JaguarPluginDefinition.class);
        List<Class> definitions = Arrays.asList(plugins);

        return definitions;
    }

    private void loadConfiguration() {
        if (logger.isInfoEnabled()) {
            logger.info("loading configuration file");
        }
        InputStream isMapping = getClass().getResourceAsStream("/jaguar.xml");

        if (isMapping != null) {
            if (logger.isInfoEnabled()) {
                logger.info("Jaguar.xml found reading");
            }
            Configuration configuration = new Configuration();
            Jaguar jaguarConfig = configuration.processXML(isMapping);

            CacheGroup globalCache = CacheFactory.getGlobalCache(SERVICE_GLOBALKEY);
            globalCache.add("jaguar-configuration", jaguarConfig);
        } else {
            if (logger.isDebugEnabled()) {
                logger.debug("Jaguar.xml not found");
            }
        }
    }

    private void initializeMapping() throws NetworkServiceException {
        if (logger.isDebugEnabled()) {
            logger.debug("initializing the network plugins");
        }
        CacheGroup globalCache = CacheFactory.getGlobalCache("NETWORKSERVICE");

        try {
            HashMap<Long, JaguarPluginDefinition> pluginDefinitionsMap = new HashMap<Long, JaguarPluginDefinition>();

            List<Class> pluginDefinitions = getPlugins();
            if (pluginDefinitions.size() > 0) {
                for (Class def : pluginDefinitions) {
                    JaguarPluginDefinition pluginDefinition = (JaguarPluginDefinition) def.newInstance();
                    for (Long requestType : pluginDefinition.getRequestTypesSupported()) {
                        pluginDefinitionsMap.put(requestType, pluginDefinition);
                    }
                }
            } else {
                if (logger.isInfoEnabled()) {
                    logger.info("Jaguar.xml not found");
                }
            }
            globalCache.add(PLUGINDEFINITIONS, pluginDefinitionsMap);
        } catch (InstantiationException ex) {
            throw new NetworkServiceException(ex);
        } catch (IllegalAccessException ex) {
            throw new NetworkServiceException(ex);
        }
        if (logger.isDebugEnabled()) {
            logger.debug("mapping finnished");
        }
    }

    private void loadJars() {
        try {
            if (logger.isDebugEnabled()) {
                logger.debug("Loading extension jars");
            }
            com.sinco.util.ClassLoader loader = com.sinco.util.ClassLoader.getInstance();

            ReaderUtil reader;
            try {
                if (logger.isDebugEnabled()) {
                    logger.debug("Loading engine network extension");
                }
                reader = new ReaderUtil("/home/cross/workspace/jaguar2/jaguar-engine-network/dist/jaguar-engine-network.jar");
                loader.loadJar(reader.readFully());
            } catch (FileNotFoundException ex) {
                logger.info("jaguar-engine-network.jar not found");
            }

            try {
                if (logger.isDebugEnabled()) {
                    logger.debug("Loading render extension");
                }
                reader = new ReaderUtil("/home/cross/workspace/jaguar2/jaguar-render-plugin/dist/jaguar-render-plugin.jar");
                loader.loadJar(reader.readFully());
            } catch (FileNotFoundException ex) {
                logger.info("jaguar-render-plugin.jar not found");
            }

            try {
                if (logger.isDebugEnabled()) {
                    logger.debug("Loading project definition");
                }
                reader = new ReaderUtil("/home/cross/workspace/jaguar2/testprocess/dist/testprocess.jar");
                loader.loadJar(reader.readFully());
            } catch (FileNotFoundException ex) {
                logger.info("testprocess.jar not found");
            }

        } catch (IOException ex) {
            logger.error(ex);
        }
    }

    private void prepareUI() {
        if (logger.isDebugEnabled()) {
            logger.debug("Preparing UI classes");
        }
        ClassLoader instance = com.sinco.util.ClassLoader.getInstance();

        List<String> resourceList = instance.getResourceList();

        HashMap<String, byte[]> screens = new HashMap<String, byte[]>();
        for (String resource : resourceList) {
            if (resource.startsWith("/forms/")) {
                try {
                    ReaderUtil reader = new ReaderUtil(instance.getResourceAsStream(resource));
                    byte[] bytes = reader.readFully();
                    String formName = resource.substring(resource.lastIndexOf("/") + 1);
                    formName = formName.substring(0, formName.indexOf("."));
                    screens.put(formName, bytes);
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
            }
        }

        processScreens(screens);
    }

    private void processScreens(HashMap<String, byte[]> screens) {
        if (logger.isDebugEnabled()) {
            logger.debug("Processing screens");
        }
        UIGenerator uIGenerator = UIGeneratorFactory.getUIGenerator(UIGeneratorType.SWING, getWorkDir());
        HashMap<Integer, byte[]> processForms = uIGenerator.processForms(screens);

        CacheFactory.getGlobalCache("METADATA").add("FORMS", processForms);
        
    }
    
    private String getWorkDir() {
        Jaguar jaguarConfig = (Jaguar) CacheFactory.getGlobalCache(SERVICE_GLOBALKEY).get("jaguar-configuration");
        return jaguarConfig.getWorkDir();
    }

    private class Listener implements Runnable {

        private NetworkService networkService;

        public Listener(NetworkService networkService) {
            this.networkService = networkService;
        }

        public void run() {
            // Notifies the parent process
            if (status != 1) {
                synchronized (networkService) {
                    networkService.notify();
                }
            }
            while (status == 1) {
                try {
                    if (server == null) {
                        synchronized (networkService) {
                            server = new ServerSocket(PORT);
                            networkService.notify();
                        }
                    }
                    logger.debug("Waiting for incomming requests");
                    Socket client = server.accept();
                    logger.debug("Incomming requests accepted");
                    new Thread(new RequestSocket(client)).start();
                } catch (SocketException ex) {
                    logger.debug("Closing server socket. Will not accept new connections");
                    status = 0;
                } catch (IOException ex) {
                    logger.error(ex);
                }
            }
        }
    }
}
