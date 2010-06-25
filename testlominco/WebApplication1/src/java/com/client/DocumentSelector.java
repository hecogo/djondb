/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.PopupPanel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.Widget;

/**
 *
 * @author cross
 */
public class DocumentSelector extends HorizontalPanel {

    private Widget docNumber;

    public DocumentSelector() {
        this(null, true);
    }

    public DocumentSelector(String docNumber, boolean enabled) {
        ClickHandler clickHandler = new ClickHandler() {

            public void onClick(ClickEvent event) {
                Window.open("Resol1737_2004_10_6_13.pdf", "_blank", null);
            }
        };
        if (enabled) {
            this.docNumber = new TextBox();
            ((TextBox) this.docNumber).setText(docNumber);
            add(this.docNumber);

            Button btn = new Button();
            btn.setText("...");
            btn.addClickHandler(clickHandler);
            add(btn);
        } else {
            this.docNumber = new Anchor(docNumber);
            ((Anchor) this.docNumber).addClickHandler(clickHandler);
            add(this.docNumber);
        }
    }
}
