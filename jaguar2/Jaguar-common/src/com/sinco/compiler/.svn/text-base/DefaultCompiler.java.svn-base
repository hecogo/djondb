/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.compiler;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileFilter;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.tools.Diagnostic;
import javax.tools.DiagnosticCollector;
import javax.tools.DiagnosticListener;
import javax.tools.JavaCompiler;
import javax.tools.JavaFileObject;
import javax.tools.StandardJavaFileManager;
import javax.tools.ToolProvider;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class DefaultCompiler extends AbstractCompiler {

    private static Log logger = LogFactory.getLog(DefaultCompiler.class);
    
    @Override
    public void compile(String srcDir, String classPath) throws CompilerException {
        try {
            JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
            DiagnosticCollector<JavaFileObject> diagnostics = new DiagnosticCollector<JavaFileObject>();

            StandardJavaFileManager fileManager = compiler.getStandardFileManager(diagnostics, null, null);
            
            File[] files = getFiles(new File(srcDir));
            
            Iterable<? extends JavaFileObject> javaFileObjects = fileManager.getJavaFileObjects(files);

            compiler.getTask(null, fileManager, diagnostics, null, null, javaFileObjects).call();

            StringBuffer errors = new StringBuffer();
            for (Diagnostic<? extends JavaFileObject> diagnostic : diagnostics.getDiagnostics()) {
                errors.append(String.format("Error on line %d in %d%n\n", diagnostic.getLineNumber(), diagnostic.getSource().toUri()));
            }
            if (errors.length() > 0) {
                logger.error(errors.toString());
            }

            fileManager.close();
            
        } catch (IOException ex) {
            throw new CompilerException(ex);
        }
        
    }

    private File[] getFiles(File dir) {

        File[] listFiles = dir.listFiles(new FileFilter() {

            public boolean accept(File pathname) {
                if (pathname.getName().endsWith(".java")) {
                    return true;
                } else {
                    return false;
                }
            }
        });
        
        ArrayList<File> result = new ArrayList<File>();
        for (File file : listFiles) {
            if (file.isDirectory()) {
                result.addAll(Arrays.asList(getFiles(file)));
            } else {
                result.add(file);
            }
        }
        return result.toArray(new File[] {});
    }

}
