/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.TextBox;

/**
 *
 * @author cross
 */
public class AdicionAlarma extends DialogBox {

    DialogBox dialog;
    
    public AdicionAlarma() {
        this.dialog = this;
        FlexTable table = new FlexTable();

        int row = 0;
        table.setHTML(row, 0, "Perfil");
        ListBox box = new ListBox();
        for (String perfil : Definitions.PERFILES) {
            box.addItem(perfil);
        }
        table.setWidget(row, 1, box);

        row++;
        table.setHTML(row, 0, "Dias");
        table.setWidget(row, 1, new TextBox());

        row++;
        table.setHTML(row, 0, "Descripcion");
        table.setWidget(row, 1, new TextBox());

        row++;
        table.setWidget(row, 0, new CheckBox("Recurrente?"));

        row++;
        row++;
        Button adicionar = new Button("Adicionar");
        adicionar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                dialog.hide();
            }
        });
        table.setWidget(row, 1, adicionar);

        add(table);
    }
}
