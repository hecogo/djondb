package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.PopupPanel;
import com.google.gwt.user.client.ui.TextBox;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author cross
 */
public class ClientSelector extends HorizontalPanel {
    TextBox nit;
    TextBox nombre;
    Button buscar;
    
    public ClientSelector() {
        nit = new TextBox();
        nit.setValue("NIT");
        nit.setWidth("100px");
        add(nit);

        nombre = new TextBox();
        nombre.setValue("NOMBRE");
        nombre.setWidth("250px");
        add(nombre);

        buscar = new Button("Buscar");
        buscar.setWidth("50px");
        buscar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                ConsultaCliente consulta = new ConsultaCliente(ConsultaCliente.TIPOCLIENTE.EXTERNO);
                consulta.center();
                consulta.show();
                nit.setValue("85785454");
                nombre.setValue("Algun cliente seleccionado");
            }
        });
        add(buscar);
    }
}
