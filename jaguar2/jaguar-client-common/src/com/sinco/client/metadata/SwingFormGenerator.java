/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client.metadata;

import com.sinco.util.ReaderUtil;
import com.sinco.util.StringUtil;
import com.sinco.util.WriterUtil;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class SwingFormGenerator implements FormGenerator {
    private static Log logger = LogFactory.getLog(SwingFormGenerator.class);
    
    private String formName;
    private byte[] definition;

    public SwingFormGenerator(String formName, byte[] definition) {
        this.formName = formName;
        this.definition = definition;
    }
    
    /**
     * generates the form files and returns the id of the generated form
     * @param destDir
     * @return form id
     */
    public int generate(String destDir) {
        if (logger.isDebugEnabled()) logger.debug(String.format("Generating %s code", formName));
        
        DigesterUtil digester = new DigesterUtil();
        ByteArrayInputStream bais = new ByteArrayInputStream(definition);
        Form form = digester.processXML(bais);
        
        generateClassFile(form, destDir);
        return form.getId();
    }

    private void generateClassFile(Form form, String destDir) {
        try {
            InputStream swingCodeIS = SwingFormGenerator.class.getResourceAsStream("/com/sinco/client/metadata/swingformtemplate.txt");
            ReaderUtil reader = new ReaderUtil(swingCodeIS);
            String template = new String(reader.readFully());
            
            template = StringUtil.replaceAll(template, "<!-- CLASSNAME -->",formName);
            
            String components = getComponentsCode(form);
            template = StringUtil.replaceAll(template, "<!-- COMPONENTS -->", components);
            
            if (!destDir.endsWith(File.separator)) {
                destDir += File.separator;
            }
            String path = destDir;
            File dir = new File(path);
            if (!dir.exists()) {
                dir.mkdirs();
            }
            WriterUtil writer = new WriterUtil(path + formName + ".java");
            writer.write(template);
            writer.close();
            if (logger.isDebugEnabled()) logger.debug(String.format("Code for %s created", formName));
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    private String getComponentsCode(Form form) {
        int x = 1;
        StringBuffer componentCode = new StringBuffer();
        for (Field field : form.getFields()) {
            componentCode.append("        TextField field" + x + " = new TextField();\n");
            componentCode.append("        field" + x + ".setRequired(true);\n");
            componentCode.append("        field" + x + ".setEditable(true);\n");
            componentCode.append("\n");
            String label = field.getLabel();
            componentCode.append("        addComponent(\"" + label + "\", field" + x+ ");\n");
            componentCode.append("\n");
            x++;
        }
        
        return componentCode.toString();
    }
}
