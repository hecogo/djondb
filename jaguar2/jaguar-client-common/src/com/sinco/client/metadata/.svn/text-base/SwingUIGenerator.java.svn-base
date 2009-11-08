/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.client.metadata;

import com.sinco.util.ReaderUtil;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import com.sinco.compiler.*;

/**
 *
 * @author cross
 */
class SwingUIGenerator implements UIGenerator {
    private static Log logger = LogFactory.getLog(SwingUIGenerator.class);
    private String workDir;
    
    public SwingUIGenerator(String workDir) {
        this.workDir = workDir;
    }

    public HashMap<Integer, byte[]> processForms(HashMap<String, byte[]> forms) {
        try {
            String sourceDestDir = getWorkDir() + "/src";
            if (logger.isDebugEnabled()) logger.debug(String.format("Processing forms into %s directory", sourceDestDir));
            HashMap<String, Integer> formIds = new HashMap<String, Integer>(forms.size());
            for (String formName : forms.keySet()) {
                byte[] bytes = forms.get(formName);
                SwingFormGenerator generator = new SwingFormGenerator(formName, bytes);
                int idForm = generator.generate(sourceDestDir);
                formIds.put(formName, idForm);
            }

            AbstractCompiler compiler = CompilerFactory.getCompiler();
            compiler.compile(sourceDestDir, "");
            
            HashMap<Integer, byte[]> formClasses = new HashMap<Integer, byte[]>(forms.size());
            for (String formName : forms.keySet()) {
                String file = sourceDestDir;
                if (!sourceDestDir.endsWith(File.separator)) {
                    sourceDestDir += File.separator;
                }
                file = sourceDestDir + formName + ".class";
                ReaderUtil reader = new ReaderUtil(file);
                byte[] classData = reader.readFully();
                int idForm = formIds.get(formName);
                formClasses.put(idForm, classData);
            }
            return formClasses;
        } catch (CompilerException ex) {
            throw new RuntimeException(ex);
        } catch (FileNotFoundException ex) {
            throw new RuntimeException(ex);
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    public String getWorkDir() {
        return workDir;
    }

    public void setWorkDir(String workDir) {
        this.workDir = workDir;
    }
}
