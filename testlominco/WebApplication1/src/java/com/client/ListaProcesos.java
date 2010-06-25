package com.client;


import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.VerticalPanel;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author cross
 */
public class ListaProcesos extends VerticalPanel {

    private String[][] data = new String[][] {
        new String[] {"1", "Waldo Perez", "Radicado", "27/Abril/2010"},
        new String[] {"15", "Acerias Paz del Rio", "Aprobado", "27/Abril/2010"},
        new String[] {"23", "Gas Natural", "Reparto", "27/Abril/2010"},
        new String[] {"24", "United Motors", "Auto de Aprobacion", "27/Abril/2010"},
        new String[] {"22", "Vicky Valencia", "Radicado", "27/Abril/2010"}
    };

    private Panel parentPanel;
    private final TIPOPANEL tipoPanel;
    
    public ListaProcesos(Panel parentPanel, TIPOPANEL tipoPanel) {
        this.parentPanel = parentPanel;
        this.tipoPanel = tipoPanel;
        initialize();
    }

    private void initialize() {
        FlexTable table = new FlexTable();
        table.setWidth("700px");

        table.setHTML(0, 2, "Proceso");
        table.setHTML(0, 3, "Actor principal");
        table.setHTML(0, 4, "Ultima etapa");
        table.setHTML(0, 5, "Fecha proxima");

        for (int x = 0; x < 5; x++) {
            final Anchor modificar = new Anchor("Modificar");
            modificar.addClickHandler(new ClickHandler() {

                public void onClick(ClickEvent event) {
                    parentPanel.clear();
                    parentPanel.add(new PanelPrincipal(tipoPanel));
                }
            });//new ClickHandlerImpl(x, parentPanel, this));
            table.setWidget(x+1, 0, modificar);
            table.setWidget(x+1, 1, new Anchor("Etapa"));
            for (int y = 0; y < 4; y++) {
                table.setHTML(x+1, y+2, data[x][y]);
            }
        }

        add(table);

    }

}
