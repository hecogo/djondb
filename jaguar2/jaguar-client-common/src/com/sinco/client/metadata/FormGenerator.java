/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client.metadata;

/**
 *
 * @author cross
 */
public interface FormGenerator {

    /**
     * generates the form files and returns the id of the generated form
     * @param destDir
     * @return form id
     */
    int generate(String destDir);
}
