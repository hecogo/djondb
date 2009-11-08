/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.util;

import java.util.Hashtable;
import javax.naming.InitialContext;
import javax.naming.NamingException;

/**
 *
 * @author cross
 */
public abstract class Context extends InitialContext {

    private static Context instance;
    private static Context instanceWithProps;

    public Context() throws NamingException {
        super();
    }

    public Context(Hashtable props) throws NamingException {
        super(props);
    }

    public static Context getInitialContext() throws NamingException {
        if (instance == null) {
            instance = new InternalContext();
        }
        return instance;
    }
    
    public static Context getInitialContext(Hashtable props) throws NamingException {
        if (instanceWithProps == null) {
            instanceWithProps = new InternalContext(props);
        }
        return instanceWithProps;
    }
    
    static class InternalContext extends Context {

        public InternalContext() throws NamingException {
            super();
        }

        public InternalContext(Hashtable props) throws NamingException {
            super(props);
        }
    }
}
