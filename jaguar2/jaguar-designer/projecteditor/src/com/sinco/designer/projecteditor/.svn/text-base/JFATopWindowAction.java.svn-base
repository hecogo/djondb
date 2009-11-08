/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.designer.projecteditor;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import org.openide.util.NbBundle;
import org.openide.util.Utilities;
import org.openide.windows.TopComponent;

/**
 * Action which shows JFATopWindow component.
 */
public class JFATopWindowAction extends AbstractAction {

    public JFATopWindowAction() {
        super(NbBundle.getMessage(JFATopWindowAction.class, "CTL_JFATopWindowAction"));
//        putValue(SMALL_ICON, new ImageIcon(Utilities.loadImage(JFATopWindowTopComponent.ICON_PATH, true)));
    }

    public void actionPerformed(ActionEvent evt) {
        TopComponent win = JFATopWindowTopComponent.findInstance();
        win.open();
        win.requestActive();
    }
}
