/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.Widget;

/**
 *
 * @author cross
 */
public class UsuariosExternos extends VerticalPanel {
    private final Panel parentPanel;

    public UsuariosExternos(Panel parent) {
        this.parentPanel = parent;
        initialize();
    }

    private void initialize() {
        FlexTable table = new FlexTable();

        ListBox ti = new ListBox();
        ti.addItem("NIT");
        ti.addItem("Cedula de ciudadania");
        addRow(table, "Tipo Identificacion", ti);
        addRow(table, "Identificacion:", new TextBox());
        addRow(table, "Nombre:", new TextBox());
        addRow(table, "Apellido:", new TextBox());
        addRow(table, "Usuario del sistema:", new TextBox());
        addRow(table, "Email", new TextBox());
        addRow(table, "Direccion", new TextBox());
        addRow(table, "Telefono", new TextBox());

        int row = table.getRowCount();
        HorizontalPanel buttonPanel = new HorizontalPanel();
        Button guardar = new Button("Guardar");
        guardar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                parentPanel.clear();
                parentPanel.add(new UsuariosExternosList(parentPanel));
            }
        });
        buttonPanel.add(guardar);
        table.setWidget(row, 1, buttonPanel);

        add(table);
    }

    private void addRow(FlexTable table, String etiqueta, Widget widget) {
        int row = table.getRowCount();

        table.setHTML(row, 0, etiqueta);
        table.setWidget(row, 1, widget);
    }
}
