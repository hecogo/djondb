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
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.VerticalPanel;
import java.util.HashMap;
import java.util.Map.Entry;

/**
 *
 * @author cross
 */
public class AdminBasica extends VerticalPanel {

    private final Panel parentPanel;

    private HashMap<String, String> getHashTiposSociedad() {
        HashMap<String, String> res = new HashMap<String, String>();

        res.put("1", "Sociedad Anonima S.A.");
        res.put("2", "En comandita simple");
        res.put("3", "Sociedad Limitada LTDA");
        res.put("4", "Sociedad por Acciones");

        return res;
    }

    private HashMap<String, String> getHashTiposDocumento() {
        HashMap<String, String> res = new HashMap<String, String>();

        res.put("1", "NIT");
        res.put("2", "Cedula de Ciudadania");
        res.put("3", "Cedula de extranjeria");
        res.put("4", "Pasaporte");

        return res;
    }

    private HashMap<String, String> getHashTiposProceso() {
        HashMap<String, String> res = new HashMap<String, String>();

        int x = 1;
        for (String tipo : Definitions.TIPOS_PROCESO) {
            res.put(String.valueOf(x), tipo);
            x++;
        }

        return res;
    }

    private HashMap<String, String> getHashEventos() {
        HashMap<String, String> res = new HashMap<String, String>();

        int x = 1;
        for (String etapa : Definitions.ETAPAS) {
            res.put(String.valueOf(x++), etapa);
        }

        return res;
    }

    public AdminBasica(Panel parent, final TIPOBASICA tipoBasica) {
        this.parentPanel = parent;
        FlexTable table = new FlexTable();

        table.setHTML(0, 2, "Id");
        table.setHTML(0, 3, "Descripcion");
        int row = 1;
        HashMap<String, String> valoresIniciales = null;
        final String titulo;
        switch (tipoBasica) {
            case TIPOSOCIEDAD:
                valoresIniciales = getHashTiposSociedad();
                break;
            case TIPODOCUMENTO:
                valoresIniciales = getHashTiposDocumento();
                break;
            case TIPOPROCESO:
                valoresIniciales = getHashTiposProceso();
                break;
            case EVENTOS:
                valoresIniciales = getHashEventos();
                break;
            default:
                throw new IllegalArgumentException();
        }
        for (Entry<String, String> entry : valoresIniciales.entrySet()) {
            table.setWidget(row, 0, new Anchor("Modificar"));
            table.setWidget(row, 1, new Anchor("Eliminar"));
            table.setHTML(row, 2, entry.getKey());
            table.setHTML(row, 3, entry.getValue());
            row++;
        }

        add(table);

        HorizontalPanel buttonPanel = new HorizontalPanel();
        buttonPanel.setHorizontalAlignment(ALIGN_RIGHT);
        Button adicionar = new Button("Adicionar");
        adicionar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                parentPanel.clear();
                parentPanel.add(new AdminBasicaSingle(parentPanel, tipoBasica));
            }
        });
        buttonPanel.add(adicionar);
        add(buttonPanel);
    }
}
