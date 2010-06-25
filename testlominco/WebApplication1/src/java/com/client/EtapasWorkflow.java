/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.client;

import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.FlexTable.FlexCellFormatter;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.VerticalPanel;

/**
 *
 * @author cross
 */
public class EtapasWorkflow extends VerticalPanel {

    private final Panel _parentPanel;
    private boolean[][] _values = new boolean[][]{
        {false, true, false, false, false, false},
        {false, false, true, false, false, false},
        {false, false, false, true, false, false},
        {false, false, false, false, true, false},
        {false, false, false, false, false, true},
        {false, false, false, false, false, false}
    };

    public EtapasWorkflow(Panel parent) {
        this._parentPanel = parent;

        initialize();
    }

    private void initialize() {
        FlexTable table = new FlexTable();
        table.setCellSpacing(6);
        FlexCellFormatter cellFormatter = table.getFlexCellFormatter();

        int row = 0;
        Label lbl = new Label("Configuracion de Etapas");
        lbl.setStyleName("label-title");
        table.setWidget(row, 0, lbl);

        row++;
        table.setHTML(row, 0, "Tipo de proceso");
        ListBox box = new ListBox();
        for (String tipo : Definitions.TIPOS_PROCESO) {
            box.addItem(tipo);
        }
        box.setWidth("100px");
        table.setWidget(row, 1, box);
        cellFormatter.setHorizontalAlignment(row, 1, ALIGN_LEFT);

        drawTable(table);

        this.add(table);
    }

    private void drawTable(FlexTable layout) {
        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();

        FlexTable table = new FlexTable();
        FlexCellFormatter flexCellFormatter = table.getFlexCellFormatter();
        table.setCellSpacing(6);

        int row = 0;
        for (int col = 0; col < Definitions.ETAPAS.length; col++) {
            Label lbl = new Label(Definitions.ETAPAS[col]);
            lbl.setStyleName("label-table-title");
            table.setWidget(row, col + 1, lbl);
            flexCellFormatter.setWidth(0, col + 1, "100px");

        }
        row++;
        for (int tableRow = 0; tableRow < Definitions.ETAPAS.length; tableRow++) {
            table.setHTML(tableRow + row, 0, Definitions.ETAPAS[tableRow]);
            for (int tableCol = 0; tableCol < Definitions.ETAPAS.length; tableCol++) {
                if (tableRow != tableCol) {
                    CheckBox box = new CheckBox();
                    box.setValue(_values[tableRow][tableCol]);
                    table.setWidget(tableRow + row, tableCol + 1, box);
                }
            }
        }

        layout.setWidget(layout.getRowCount(), 0, table);
        cellFormatter.setColSpan(layout.getRowCount() - 1, 0, 2);
    }
}
