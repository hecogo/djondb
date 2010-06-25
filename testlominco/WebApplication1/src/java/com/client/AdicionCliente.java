/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.Panel;

/**
 *
 * @author cross
 */
public class AdicionCliente extends DialogBox {

    DialogBox dialog;
    
    public AdicionCliente() {
        this.dialog = this;
        FlexTable table = new FlexTable();

        table.setHTML(0, 0, "Tipo de vinculo");
        ListBox box = new ListBox();
        box.addItem("Demandante Principal");
        box.addItem("Representante Legal - Demandado");
        box.addItem("Demandado");
        table.setWidget(0, 1, box);

        table.setHTML(1, 0, "Cliente");
        table.setWidget(1, 1, new ClientSelector());

        Button adicionar = new Button("Adicionar");
        adicionar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                dialog.hide();
            }
        });
        table.setWidget(2, 1, adicionar);

        add(table);
    }
}
