/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.compiler;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import junit.framework.TestCase;

/**
 *
 * @author cross
 */
public class DefaultCompilerTest extends TestCase {
    
    public DefaultCompilerTest(String testName) {
        super(testName);
    }            

    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    /**
     * Test of compile method, of class DefaultCompiler.
     */
    public void testCompile() {
        try {
            System.out.println("compile");
           String srcDir = createTemporalFiles();
            String sourceDestDir = System.getProperty("java.io.tmpdir");
            if (!sourceDestDir.endsWith(File.separator)) {
                sourceDestDir += File.separator;
            }

            String classPath = "";
            DefaultCompiler instance = new DefaultCompiler();
            instance.compile(srcDir, classPath);
        } catch (Exception ex) {
            ex.printStackTrace();
            fail(ex.getMessage());
        }
    }

    private void createTemp(String sourceDestDir, String className) throws IOException, FileNotFoundException {

        String fileContent = "public class " + className + " {\n public " + className + "() {\n System.out.println(\"Hello world\");\n}\n}";
        String fileName = sourceDestDir.endsWith(File.separator) ? sourceDestDir : sourceDestDir + File.separator;
        fileName += "/" + className + ".java";

        File file = new File(sourceDestDir);
        file.mkdirs();

        FileOutputStream fos = new FileOutputStream(fileName);
        fos.write(fileContent.getBytes());
        fos.close();
    }

    private String createTemporalFiles() throws IOException {
        String sourceDestDir = System.getProperty("java.io.tmpdir") + "/testsrc";
        createTemp(sourceDestDir, "Temp");
        createTemp(sourceDestDir, "MyClass");
         
        return sourceDestDir;
    }

}
