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
public class AdminBasicaSingle extends VerticalPanel {
    private Panel parentPanel;
    private final TIPOBASICA tipoBasica;

    public AdminBasicaSingle(Panel parentPanel, TIPOBASICA tipoBasica) {
        this.tipoBasica = tipoBasica;
        this.parentPanel = parentPanel;
        initialize();
    }

    private void initialize() {
        FlexTable table = new FlexTable();

        final String titulo;
        switch (tipoBasica) {
            case TIPOSOCIEDAD:
                titulo = "Tipos de Sociedad";
                break;
            case TIPODOCUMENTO:
                titulo = "Tipos de Documento";
                break;
            case TIPOPROCESO:
                titulo = "Tipos de Proceso";
                break;
            case EVENTOS:
                titulo = "Etapas";
                break;
            default:
                throw new IllegalArgumentException();
        }
        table.setHTML(0, 0, titulo);
        FlexCellFormatter flexCellFormatter = table.getFlexCellFormatter();
        flexCellFormatter.setColSpan(0, 0, 2);

        table.setHTML(1, 0, "Codigo");
        table.setWidget(1, 1, new TextBox());

        table.setHTML(2, 0, "Descripcion");
        table.setWidget(2, 1, new TextBox());

        HorizontalPanel buttonPanel = new HorizontalPanel();
        Button aceptar = new Button("Guardar");
        ClickHandler handler = new ClickHandler() {

            public void onClick(ClickEvent event) {
                parentPanel.clear();
                parentPanel.add(new AdminBasica(parentPanel, tipoBasica));
            }
        };
        aceptar.addClickHandler(handler);
        buttonPanel.add(aceptar);
        Button cancelar = new Button("Cancelar");
        cancelar.addClickHandler(handler);
        buttonPanel.add(cancelar);
        table.setWidget(3, 0, buttonPanel);
        flexCellFormatter.setColSpan(3, 0, 2);
        flexCellFormatter.setHorizontalAlignment(3, 0, ALIGN_RIGHT);

        add(table);
    }
}
