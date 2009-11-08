/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client.metadata;

/**
 *
 * @author cross
 */
public class UIGeneratorFactory {
    
    public static UIGenerator getUIGenerator(UIGeneratorType type, String workDir) {
        switch (type) {
            case SWING:
                return new SwingUIGenerator(workDir);
            default:
                throw new IllegalArgumentException(String.format("Type %s not supported", type));
        }
    }
}
