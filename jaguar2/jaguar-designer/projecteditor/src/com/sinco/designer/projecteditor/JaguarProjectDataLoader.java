/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.designer.projecteditor;

import java.io.IOException;
import org.openide.filesystems.FileObject;
import org.openide.loaders.DataObjectExistsException;
import org.openide.loaders.MultiDataObject;
import org.openide.loaders.UniFileLoader;
import org.openide.util.NbBundle;

public class JaguarProjectDataLoader extends UniFileLoader {

    public static final String REQUIRED_MIME = "text/x-jfa";
    private static final long serialVersionUID = 1L;

    public JaguarProjectDataLoader() {
        super("com.sinco.designer.projecteditor.JaguarProjectDataObject");
    }

    @Override
    protected String defaultDisplayName() {
        return NbBundle.getMessage(JaguarProjectDataLoader.class, "LBL_JaguarProject_loader_name");
    }

    @Override
    protected void initialize() {
        super.initialize();
        getExtensions().addMimeType(REQUIRED_MIME);
    }

    protected MultiDataObject createMultiObject(FileObject primaryFile) throws DataObjectExistsException, IOException {
        return new JaguarProjectDataObject(primaryFile, this);
    }

    @Override
    protected String actionsContext() {
        return "Loaders/" + REQUIRED_MIME + "/Actions";
    }
}
