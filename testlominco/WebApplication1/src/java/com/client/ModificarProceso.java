/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.FlexTable.FlexCellFormatter;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;

/**
 *
 * @author cross
 */
public class ModificarProceso extends VerticalPanel {

    private final Panel rootPanel;
    private final TIPOPANEL tipoPanel;

    public ModificarProceso(Panel rootPanel, TIPOPANEL tipoPanel) {
        this.rootPanel = rootPanel;
        this.tipoPanel = tipoPanel;
        crearConsulta();
    }

    private void crearConsulta() {
        FlexTable layout = new FlexTable();
        FlexCellFormatter flexCellFormatter = layout.getFlexCellFormatter();

        layout.setCellPadding(6);

        layout.setHTML(0, 0, "Numero radicacion");
        layout.setWidget(0, 1, new TextBox());

        layout.setHTML(1, 0, "Identificacion demandante principal");
        layout.setWidget(1, 1, new TextBox());

        layout.setHTML(2, 0, "Identificacion demandando principal");
        layout.setWidget(2, 1, new TextBox());

        HorizontalPanel buttonPanel = new HorizontalPanel();
        Button consultar = new Button("Consultar");
        consultar.addClickHandler(new ClickHandler() {
            public void onClick(ClickEvent event) {
                addListaProcesos();
            }
        });
        buttonPanel.add(consultar);

        layout.setWidget(3, 1, buttonPanel);

        add(layout);
    }

    private void addListaProcesos() {
        ListaProcesos procesos = new ListaProcesos(rootPanel, tipoPanel);
        this.add(procesos);
    }
}
