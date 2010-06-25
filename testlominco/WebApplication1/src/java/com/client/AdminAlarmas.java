/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.client;

import com.google.gwt.event.dom.client.ChangeEvent;
import com.google.gwt.event.dom.client.ChangeHandler;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.FlexTable.FlexCellFormatter;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.VerticalPanel;
import java.util.Random;

/**
 *
 * @author cross
 */
public class AdminAlarmas extends VerticalPanel {

    private final Panel _parentPanel;

    public AdminAlarmas(Panel panelPrincipal) {
        this._parentPanel = panelPrincipal;

        initialize();
    }

    private void initialize() {
        final FlexTable layout = new FlexTable();

        layout.setCellSpacing(6);

        int row = 0;
        layout.setHTML(row, 0, "Tipo de Proceso");
        ListBox box = new ListBox();
        for (String tipo : Definitions.TIPOS_PROCESO) {
            box.addItem(tipo);
        }
        layout.setWidget(row, 1, box);

        row++;
        layout.setHTML(row, 0, "Etapa");
        ListBox box2 = new ListBox();
        box2.addChangeHandler(new ChangeHandler() {

            public void onChange(ChangeEvent event) {
                drawTable(layout, 2);
            }
        });
        for (String etapa : Definitions.ETAPAS) {
            box2.addItem(etapa);
        }
        layout.setWidget(row, 1, box2);

        row++;
        drawTable(layout, 2);

        row++;
        Button btn = new Button();
        btn.setText("Adicionar Alarma");
        btn.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                AdicionAlarma addAlarma = new AdicionAlarma();
                addAlarma.center();
                addAlarma.show();
            }
        });
        layout.setWidget(row, 1, btn);

        add(layout);
    }

    private void drawTable(FlexTable layout, int row) {
        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();

        layout.setHTML(row, 0, "Alarmas");

        FlexTable table = new FlexTable();
        table.setCellSpacing(6);

        int tableRow = 0;
        table.setHTML(tableRow, 0, "Perfil");
        table.setHTML(tableRow, 1, "Dias");
        table.setHTML(tableRow, 2, "Descripcion");
        table.setHTML(tableRow, 3, "Recurrente");

        tableRow++;
        table.setHTML(tableRow, 0, "Coordinador");
        int dias = 0;
        while ((dias <= 20) || (dias >= 50)) {
            dias = (int) (Math.random() * 100.0);
        }
        table.setHTML(tableRow, 1, String.valueOf(dias));
        table.setHTML(tableRow, 2, "Vencimiento de terminos para etapa");
        table.setHTML(tableRow, 3, "No");

        tableRow++;
        table.setHTML(tableRow, 0, "Ponente");
        dias = 0;
        while ((dias <= 5) || (dias >= 20)) {
            dias = (int) (Math.random() * 100.0);
        }
        table.setHTML(tableRow, 1, String.valueOf(dias));
        table.setHTML(tableRow, 2, "Vencimiento de terminos para etapa");
        table.setHTML(tableRow, 3, "Si");

        cellFormatter.setColSpan(row, 0, 2);
        layout.setWidget(row, 0, table);
    }
}
