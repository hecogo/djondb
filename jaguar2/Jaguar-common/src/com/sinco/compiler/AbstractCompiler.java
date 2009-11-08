/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.compiler;

/**
 *
 * @author cross
 */
public abstract class AbstractCompiler {

    public abstract void compile(String srcDir, String classPath) throws CompilerException;
}
