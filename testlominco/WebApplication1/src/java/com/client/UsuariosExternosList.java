/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Anchor;
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
public class UsuariosExternosList extends VerticalPanel {

    FlexTable listaUsuarios;
    private final Panel parentPanel;

    public UsuariosExternosList(Panel destination) {
        this.parentPanel = destination;
        FlexTable table = new FlexTable();

        table.setHTML(0, 0, "Nombre:");
        table.setWidget(0, 1, new TextBox());

        HorizontalPanel horizontal = new HorizontalPanel();
        Button buscar = new Button("Buscar");
        buscar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                mostrarListaUsuarios();
            }
        });
        horizontal.add(buscar);
        Button nuevo = new Button("Nuevo");
        nuevo.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                parentPanel.clear();
                parentPanel.add(new UsuariosExternos(parentPanel));
            }
        });
        horizontal.add(nuevo);
        table.setWidget(1, 1, horizontal);
        FlexCellFormatter flexCellFormatter = table.getFlexCellFormatter();
        flexCellFormatter.setHorizontalAlignment(1, 1, ALIGN_RIGHT);

        add(table);
        
        listaUsuarios = new FlexTable();
        listaUsuarios.setVisible(false);

        add(listaUsuarios);
    }

    private void mostrarListaUsuarios() {
        listaUsuarios.setHTML(0, 1, "Nombre");
        
        addUsuario("Pedro Perez");
        addUsuario("Socios de Colombia");
        addUsuario("Maduros Importadores");
        addUsuario("Andres Gonzalez");
        addUsuario("Deportes Lola");
        addUsuario("Sistemas de Computo");
        listaUsuarios.setVisible(true);
    }

    private void addUsuario(String nombre) {
        int row = listaUsuarios.getRowCount();

        listaUsuarios.setWidget(row, 0, new Anchor("Modificar"));
        listaUsuarios.setHTML(row, 1, nombre);
    }
}
