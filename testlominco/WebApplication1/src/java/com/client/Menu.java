/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.client;

import com.google.gwt.event.dom.client.MouseDownEvent;
import com.google.gwt.event.dom.client.MouseDownHandler;
import com.google.gwt.event.logical.shared.SelectionEvent;
import com.google.gwt.event.logical.shared.SelectionHandler;
import com.google.gwt.user.client.ui.DecoratedStackPanel;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.Tree;
import com.google.gwt.user.client.ui.TreeItem;
import com.google.gwt.user.client.ui.VerticalPanel;
import java.util.HashMap;

/**
 *
 * @author cross
 */
public class Menu extends VerticalPanel {
    private final Panel destination;

    public Menu(Panel destination) {
        this.destination = destination;
        initialize();
    }

    private void initialize() {
        DecoratedStackPanel stackPanel = new DecoratedStackPanel();
        stackPanel.setWidth("200px");
        stackPanel.add(crearItemsAdministracion(), "Administracion", true);
        stackPanel.add(crearItemsProceso(), "Proceso", true);
        add(stackPanel);
    }

    private Tree crearItemsAdministracion() {
        Tree menu = new Tree();
        menu.addItem("Tipos de Sociedad");
        menu.addItem("Tipos de Documento");
        menu.addItem("Tipos de Proceso");
        menu.addItem("Workflow de Etapas");
        menu.addItem("Etapas");
        menu.addItem("Usuarios Externos");
        menu.addItem("Alarmas");
        menu.addSelectionHandler(new SelectionHandler<TreeItem>() {

            public void onSelection(SelectionEvent<TreeItem> event) {
                TreeItem selectedItem = event.getSelectedItem();
                if (selectedItem.getText().equalsIgnoreCase("Tipos de Sociedad")) {
                    destination.clear();
                    destination.add(new AdminBasica(destination, TIPOBASICA.TIPOSOCIEDAD));
                }
                if (selectedItem.getText().equalsIgnoreCase("Tipos de Documento")) {
                    destination.clear();
                    destination.add(new AdminBasica(destination, TIPOBASICA.TIPODOCUMENTO));
                }
                if (selectedItem.getText().equalsIgnoreCase("Tipos de Proceso")) {
                    destination.clear();
                    destination.add(new AdminBasica(destination, TIPOBASICA.TIPOPROCESO));
                }
                if (selectedItem.getText().equalsIgnoreCase("Etapas")) {
                    destination.clear();
                    destination.add(new AdminBasica(destination, TIPOBASICA.EVENTOS));
                }
                if (selectedItem.getText().equalsIgnoreCase("Usuarios Externos")) {
                    destination.clear();
                    destination.add(new UsuariosExternosList(destination));
                }
                if (selectedItem.getText().equalsIgnoreCase("Workflow de Etapas")) {
                    destination.clear();
                    destination.add(new EtapasWorkflow(destination));
                }
                if (selectedItem.getText().equalsIgnoreCase("Alarmas")) {
                    destination.clear();
                    destination.add(new AdminAlarmas(destination));
                }
            }

        });
        return menu;
    }

    public Tree crearItemsProceso() {
        Tree menu = new Tree();
        menu.addItem("Mis Procesos");
        menu.addItem("Radicar Proceso");
        menu.addItem("Modificar Proceso");
//        menu.addItem("Registrar evento");
        menu.addSelectionHandler(new SelectionHandler<TreeItem>() {

            public void onSelection(SelectionEvent<TreeItem> event) {
                TreeItem selectedItem = event.getSelectedItem();
                if (selectedItem.getText().equalsIgnoreCase("Radicar Proceso")) {
                    destination.clear();
                    destination.add(new PanelPrincipal(TIPOPANEL.MODIFICACION));
                }
                if (selectedItem.getText().equalsIgnoreCase("Mis Procesos")) {
                    destination.clear();
                    destination.add(new ListaProcesos(destination, TIPOPANEL.MODIFICACION));
                }
                if (selectedItem.getText().equalsIgnoreCase("Registrar evento")) {
                    destination.clear();
                    destination.add(new ModificarProceso(destination, TIPOPANEL.EVENTO));
                }
                if (selectedItem.getText().equalsIgnoreCase("Modificar Proceso")) {
                    destination.clear();
                    destination.add(new ModificarProceso(destination, TIPOPANEL.MODIFICACION));
                }
            }
            
        });
        return menu;
    }

}
