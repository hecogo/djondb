/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.designer.projecteditor;

import org.openide.DialogDisplayer;
import org.openide.NotifyDescriptor;
import org.openide.filesystems.FileObject;
import org.openide.filesystems.FileUtil;
import org.openide.nodes.Node;
import org.openide.util.HelpCtx;
import org.openide.util.NbBundle;
import org.openide.util.actions.CookieAction;

public final class EditProject extends CookieAction {

    protected void performAction(Node[] activatedNodes) {
        JaguarProjectDataObject jaguarProjectDataObject = activatedNodes[0].getLookup().lookup(JaguarProjectDataObject.class);
        FileObject f = jaguarProjectDataObject.getPrimaryFile();
	String displayName = FileUtil.getFileDisplayName(f);
	String msg = "I am " + displayName + ". Hear me roar!"; 
        NotifyDescriptor nd = new NotifyDescriptor.Message(msg);
        DialogDisplayer.getDefault().notify(nd);
    }

    protected int mode() {
        return CookieAction.MODE_EXACTLY_ONE;
    }

    public String getName() {
        return NbBundle.getMessage(EditProject.class, "CTL_EditProject");
    }

    protected Class[] cookieClasses() {
        return new Class[]{JaguarProjectDataObject.class};
    }

    @Override
    protected String iconResource() {
        return "com/sinco/designer/projecteditor/edit.png";
    }

    public HelpCtx getHelpCtx() {
        return HelpCtx.DEFAULT_HELP;
    }

    @Override
    protected boolean asynchronous() {
        return false;
    }
}

