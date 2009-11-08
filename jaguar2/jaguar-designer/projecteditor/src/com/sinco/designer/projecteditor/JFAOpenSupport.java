/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.designer.projecteditor;

import org.openide.cookies.CloseCookie;
import org.openide.cookies.OpenCookie;
import org.openide.loaders.OpenSupport;
import org.openide.windows.CloneableTopComponent;

/**
 *
 * @author cross
 */
class JFAOpenSupport extends OpenSupport implements OpenCookie, CloseCookie {

    public JFAOpenSupport(JaguarProjectDataObject.Entry entry) {
        super(entry);
    }

    protected CloneableTopComponent createCloneableTopComponent() {
        JaguarProjectDataObject dobj = (JaguarProjectDataObject) entry.getDataObject();
        JFATopWindowTopComponent tc = new JFATopWindowTopComponent(dobj);
        tc.setDisplayName(dobj.getName());
        return tc;
    }
}
