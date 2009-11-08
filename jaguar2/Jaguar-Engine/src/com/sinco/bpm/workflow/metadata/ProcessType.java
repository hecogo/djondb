/*
 * ProcessType.java
 *
 * Created on 7 July 2007, 12:27
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow.metadata;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

/**
 *
 * @author cross
 */
public enum ProcessType implements Serializable {
    NONE,
    PRIVATE,
    ABSTRACT,
    COLLABORATION;
    
    
}
