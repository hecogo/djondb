/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;

/**
 *
 * @author cross
 */
public class ConsultaCliente extends DialogBox {

    VerticalPanel vpanel;
    final ConsultaCliente dialogBox;

    public String nombreSelected;
    public String idSelected;

    public enum TIPOCLIENTE {
        INTERNO,
        EXTERNO
    }
    private TIPOCLIENTE _tipoCliente;

    public ConsultaCliente(TIPOCLIENTE tipoCliente) {
        dialogBox = this;
        _tipoCliente = tipoCliente;
        setText("Busqueda de personas");
        setGlassEnabled(true);
        vpanel = new VerticalPanel();

        FlexTable layout = new FlexTable();

        layout.setHTML(0, 0, "Identificacion");
        layout.setWidget(0, 1, new TextBox());

        layout.setHTML(1, 0, "Nombre");
        TextBox nombre = new TextBox();
        nombre.setValue("Perez");
        layout.setWidget(1, 1, nombre);

        HorizontalPanel buttonPanel = new HorizontalPanel();
        Button buscar = new Button("Buscar");
        buttonPanel.add(buscar);
        buscar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                doSearch();
            }
        });
        Button cerrar = new Button("Cancelar");
        buttonPanel.add(cerrar);
        cerrar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                dialogBox.hide();
            }
        });
        layout.setWidget(2, 0, buttonPanel);
        vpanel.add(layout);
        this.add(vpanel);
    }

    private void doSearch() {
        FlexTable grid = createGridResult();
        vpanel.add(grid);
//        center();
    }

    private FlexTable createGridResult() {
        FlexTable table = new FlexTable();
        table.setHTML(0, 1, "Nombre");
        if (_tipoCliente == TIPOCLIENTE.INTERNO) {
            table.setHTML(0, 2, "Perfil");
        }

        addRow(table, "Perez Carlos Alejandro", "Delegado");
        addRow(table, "Gomez Perez Martin", "Coordinador");
        addRow(table, "Circo Perez Martin", "Ponente");
        addRow(table, "Perez Rodriguez Maria", "Ponente");
        addRow(table, "Rosero Perez Ximena", "Ponente");
        addRow(table, "Perez Carlos Alejandro", "Coordinador");
        addRow(table, "Perez Marina", "Ponente");

        return table;
    }

    void addRow(FlexTable table, final String nombre, final String perfil) {
        int row = table.getRowCount();
        Anchor anchor = new Anchor("seleccionar");
        ClickHandler handler = new ClickHandler() {

            public void onClick(ClickEvent event) {
                dialogBox.idSelected = "52451542";
                dialogBox.nombreSelected = nombre;
                System.out.println("From Dialog: idSelected" + idSelected);
                dialogBox.hide();
            }
        };
        anchor.addClickHandler(handler);
        table.setWidget(row, 0, anchor);
        table.setHTML(row, 1, nombre);
        if (_tipoCliente == TIPOCLIENTE.INTERNO) {
            table.setHTML(row, 2, perfil);
        }
    }
}
