/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.logical.shared.ValueChangeEvent;
import com.google.gwt.event.logical.shared.ValueChangeHandler;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.DecoratedTabPanel;
import com.google.gwt.user.client.ui.FileUpload;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.FlexTable.FlexCellFormatter;
import com.google.gwt.user.client.ui.HasHorizontalAlignment;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.TabPanel;
import com.google.gwt.user.client.ui.TextArea;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.datepicker.client.DateBox;
import com.google.gwt.user.datepicker.client.DatePicker;
import java.util.Date;

/**
 *
 * @author cross
 */
public class PanelPrincipal extends VerticalPanel {

    private TabPanel tab;
    private TIPOPANEL tipoPanel;
    private FlexTable etapasLayout;

    public PanelPrincipal(TIPOPANEL tipoPanel) {
        this.tipoPanel = tipoPanel;
        tab = new DecoratedTabPanel();

        primerPanel();
        segundoPanel();
        tercerPanel();
        cuartoPanel();
        panelAutorizaciones();
        panelPolizas();
        panelInformacionFinanciera();
        panelEtapas();
        panelAlarmas();

        tab.selectTab(0);
        this.add(tab);

        HorizontalPanel buttonPanel = new HorizontalPanel();
        Button guardar = new Button("Guardar");
        buttonPanel.add(guardar);
        Button cancelar = new Button("Cancelar");
        buttonPanel.add(cancelar);
        add(buttonPanel);

    }

    private FlexTable panelUsuarios(int tipo) {
        FlexTable layout = new FlexTable();

        layout.setHTML(0, 2, "Tipo Vinculo");
        layout.setHTML(0, 3, "Nombre");

        addUsuario(layout, "Representante Legal - Demandado", "Mariano Lopez");
        addUsuario(layout, "Representante Legal - Demandante", "Mauricio Moran");
        if (tipo == 2) {
            addUsuario(layout, "Demandado", "Andrea Zafra");
            addUsuario(layout, "Demandado", "Andres Martin");
            addUsuario(layout, "Demandado", "Marina Lafuente");
            addUsuario(layout, "Demandante", "Francisco Ruiz");
        }

        return layout;
    }

    private void primerPanel() {
        FlexTable layout = new FlexTable();
        layout.setCellSpacing(6);
        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();

        int row = 1;
        // Add some standard form options
        layout.setHTML(row, 0, "Numero de Radicacion");
        layout.setWidget(row, 1, new TextBox());
        layout.setHTML(row, 2, "Fecha de Radicacion");
        DateBox dateBox = new DateBox();
        dateBox.setValue(new Date());
        layout.setWidget(1, 3, dateBox);

        row++;
        layout.setHTML(row, 0, "Tipo de Proceso");
        ListBox drop = new ListBox();
        for (String tipo : Definitions.TIPOS_PROCESO) {
            drop.addItem(tipo);
        }
        layout.setWidget(row, 1, drop);

        layout.setHTML(row, 2, "Dependecia");
        ListBox drop2 = new ListBox();
        drop2.addItem("Dependencia 1");
        drop2.addItem("Dependencia 2");
        layout.setWidget(row, 3, drop2);

        row++;
        layout.setHTML(row, 0, "Descripcion corta");
        TextBox descripcioncorta = new TextBox();
        layout.setWidget(row, 1, descripcioncorta);
        descripcioncorta.setWidth("400px");
        cellFormatter.setColSpan(row, 1, 3);
        cellFormatter.setHorizontalAlignment(row, 1,
                HasHorizontalAlignment.ALIGN_LEFT);

        row++;
        layout.setHTML(row, 0, "Origen:");
        ListBox drop3 = new ListBox();
        drop3.addItem("Abandono de los negocios");
        drop3.addItem("Fracaso o incumplimiento de un acuerdo de reestructuración");
        drop3.addItem("Solicitud directa del deudor");
        layout.setWidget(row, 1, drop3);

        row++;
        layout.setWidget(row, 0, panelUsuarios(1));
        cellFormatter.setColSpan(row, 0, 4);
        VerticalPanel panel = new VerticalPanel();
        panel.add(layout);
        tab.add(panel, "Tapa del proceso");
    }

    private void segundoPanel() {
        FlexTable layout = new FlexTable();

        layout.setCellSpacing(6);
        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();

        // Add a title to the form
        layout.setHTML(0, 0, "Documento");
        layout.setHTML(0, 1, "Descripcion");
        layout.setHTML(0, 2, "Fecha de radicado");
        layout.setHTML(0, 3, "Etapa");
        layout.setHTML(0, 4, "Publico");

        addDocumento(layout, "01-2521-253", "Demanda", "2010/01/20", Definitions.ETAPAS[0], true);
        addDocumento(layout, "01-2521-253", "Acta de Reparto", "2010/01/22", Definitions.ETAPAS[1], false);
        addDocumento(layout, "01-2521-253", "Auto de aprobacion", "2010/01/25", Definitions.ETAPAS[2], true);
        addDocumento(layout, "01-2521-253", "Recurso de reposicion", "2010/01/30", Definitions.ETAPAS[2], true);


        HorizontalPanel buttonPanel = new HorizontalPanel();
        buttonPanel.setHorizontalAlignment(ALIGN_RIGHT);
        buttonPanel.add(new Button("Adicionar Documento"));
        layout.setWidget(layout.getRowCount(), 0, buttonPanel);
        cellFormatter.setColSpan(layout.getRowCount() - 1, 0, 3);

        VerticalPanel panel = new VerticalPanel();
        panel.add(layout);
        tab.add(panel, "Documentos asociados");
    }

    private void addDocumento(FlexTable layout, String radicacion, String descCorta, String fecha, String evento, boolean visible) {
        int row = layout.getRowCount();
        layout.setWidget(row, 0, new DocumentSelector(radicacion, false));
        layout.setHTML(row, 1, descCorta);
        layout.setHTML(row, 2, fecha);
        layout.setHTML(row, 3, evento);
        CheckBox box = new CheckBox();
        box.setValue(visible);
        layout.setWidget(row, 4, box);
    }

    private void addAutorizacion(FlexTable layout, String codigoAutorizacion, String descCorta, String documento) {
        int row = layout.getRowCount();
        layout.setHTML(row, 0, codigoAutorizacion);
        layout.setWidget(row, 1, new Anchor(descCorta));
        layout.setWidget(row, 2, new DocumentSelector(documento, false));
    }

    private void tercerPanel() {
        FlexTable layout = new FlexTable();
        layout.setHTML(0, 2, "Perfil");
        layout.setHTML(0, 3, "Nombre");
        addUsuario(layout, "Delegado", "Miguel Sanchez");
        addUsuario(layout, "Coordinador", "Pedro Perez");
        addUsuario(layout, "Secretario", "Juan Hernandez");
        addUsuario(layout, "Ponente", "Alicia Marin");

        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();
        HorizontalPanel buttonPanel = new HorizontalPanel();
        int row = layout.getRowCount();
        layout.setWidget(row, 0, buttonPanel);
        cellFormatter.setColSpan(row, 0, 4);
        cellFormatter.setHorizontalAlignment(row, 0,
                HasHorizontalAlignment.ALIGN_RIGHT);

        Button guardar = new Button("Adicionar Usuario");
        guardar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                ConsultaCliente consultar = new ConsultaCliente(ConsultaCliente.TIPOCLIENTE.INTERNO);
                consultar.center();
                consultar.show();
            }
        });
        buttonPanel.add(guardar);

        VerticalPanel panel = new VerticalPanel();
        panel.add(layout);
        tab.add(panel, "Funcionarios");
    }

    private void addUsuario(FlexTable layout, String role, String nombre) {
        int row = layout.getRowCount();
        layout.setWidget(row, 0, new Anchor("Modificar"));
        layout.setWidget(row, 1, new Anchor("Remover"));
        layout.setHTML(row, 2, role);
        layout.setHTML(row, 3, nombre);
    }

    private void cuartoPanel() {
        FlexTable layout = panelUsuarios(2);

        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();

        HorizontalPanel buttonPanel = new HorizontalPanel();
        int row = layout.getRowCount();
        layout.setWidget(row, 0, buttonPanel);
        cellFormatter.setColSpan(row, 0, 4);
        cellFormatter.setHorizontalAlignment(row, 0,
                HasHorizontalAlignment.ALIGN_RIGHT);

        Button guardar = new Button("Adicionar Usuario");
        buttonPanel.add(guardar);
        guardar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                AdicionCliente adicionar = new AdicionCliente();
                adicionar.center();
                adicionar.show();
            }
        });

        VerticalPanel panel = new VerticalPanel();
        panel.add(layout);
        tab.add(panel, "Usuarios Demanda");
    }

    private void panelPolizas() {
        FlexTable layout = new FlexTable();

        layout.setCellSpacing(6);
        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();

        // Add a title to the form
        layout.setHTML(0, 0, "Tipo de Poliza");
        layout.setHTML(0, 1, "Descripcion");
        layout.setHTML(0, 2, "Documento asociado");
        layout.setHTML(0, 3, "Fecha de inicio");
        layout.setHTML(0, 4, "Fecha de fin");

        addPoliza(layout, "Garantia de cumplimiento", "Poliza comercial de seguros", "01-2525-245", "2010/01/01", "2011/01/01");
        addPoliza(layout, "Responsabilidad civil de cobertura", "Poliza de cobertura de responsabilidad contraactual", "01-2526-245", "2010/01/01", "2010/06/01");

        HorizontalPanel buttonPanel = new HorizontalPanel();
        buttonPanel.setHorizontalAlignment(ALIGN_RIGHT);
        Button adicionarPoliza = new Button("Adicionar Poliza");
        adicionarPoliza.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
                throw new UnsupportedOperationException("Not supported yet.");
            }
        });
        buttonPanel.add(adicionarPoliza);
        layout.setWidget(layout.getRowCount(), 0, buttonPanel);
        cellFormatter.setColSpan(layout.getRowCount() - 1, 0, 3);

        VerticalPanel panel = new VerticalPanel();
        panel.add(layout);
        tab.add(panel, "Polizas");
    }

    private void panelEtapas() {
        etapasLayout = new FlexTable();

        etapasLayout.setCellSpacing(6);
        FlexCellFormatter cellFormatter = etapasLayout.getFlexCellFormatter();

        int row = 0;
        etapasLayout.setHTML(row, 0, "Etapa Actual:");
        etapasLayout.setHTML(row, 1, Definitions.ETAPAS[3]);
        row++; // 1
        CheckBox cumplida = new CheckBox("Cumplida?");
        cumplida.addValueChangeHandler(new ValueChangeHandler<Boolean>() {

            public void onValueChange(ValueChangeEvent<Boolean> event) {
                boolean visible = event.getValue();
                for (int x = 2; x <= 5; x++) {
                    FlexCellFormatter cellFormatter = etapasLayout.getFlexCellFormatter();
                    cellFormatter.setVisible(x, 0, visible);
                    cellFormatter.setVisible(x, 1, visible);
                }
            }
        });
        etapasLayout.setWidget(row, 0, cumplida);

        row++; // 2
        etapasLayout.setHTML(row, 0, "Documento de gestion:");
        etapasLayout.setWidget(row, 1, new DocumentSelector());
        cellFormatter.setVisible(row, 0, false);
        cellFormatter.setVisible(row, 1, false);

        row++; // 3
        etapasLayout.setHTML(row, 0, "Notas");
        cellFormatter.setVisible(row, 0, false);
        cellFormatter.setVisible(row, 1, false);
        row++; // 4
        TextArea notes = new TextArea();
        notes.setVisibleLines(5);
        notes.setCharacterWidth(40);
        etapasLayout.setWidget(row, 0, notes);
        cellFormatter.setColSpan(row, 0, 3);
        cellFormatter.setVisible(row, 0, false);
        cellFormatter.setVisible(row, 1, false);

        row++; // 5
        etapasLayout.setHTML(row, 0, "Nueva Etapa:");
        ListBox etapas = new ListBox();
        etapas.addItem(Definitions.ETAPAS[4]);
        etapas.addItem(Definitions.ETAPAS[5]);
        etapasLayout.setWidget(row, 1, etapas);
        cellFormatter.setVisible(row, 0, false);
        cellFormatter.setVisible(row, 1, false);

        row++; // 6
        FlexTable table = new FlexTable();
        int tableRow = 0;
        table.setHTML(tableRow, 0, "Etapa");
        table.setHTML(tableRow, 1, "Documento gestion");
        table.setHTML(tableRow, 2, "Fecha de Inicio");
        table.setHTML(tableRow, 3, "Fecha de finalizacion");

        tableRow++;
        table.setHTML(tableRow, 0, Definitions.ETAPAS[0]);
        table.setWidget(tableRow, 1, new DocumentSelector("2010-01-021221", false));
        table.setHTML(tableRow, 2, "2010-01-02");
        table.setHTML(tableRow, 3, "2010-01-10");

        tableRow++;
        table.setHTML(tableRow, 0, Definitions.ETAPAS[1]);
        table.setWidget(tableRow, 1, new DocumentSelector("2010-01-021224", false));
        table.setHTML(tableRow, 2, "2010-01-15");
        table.setHTML(tableRow, 3, "2010-01-25");

        cellFormatter.setColSpan(row, 0, 2);
        etapasLayout.setWidget(row, 0, table);

        VerticalPanel panel = new VerticalPanel();
        panel.add(etapasLayout);
        tab.add(panel, "Etapas");
    }

    private void panelAutorizaciones() {
        FlexTable layout = new FlexTable();

        layout.setCellSpacing(6);
        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();

        // Add a title to the form
        layout.setHTML(0, 0, "Codigo Autorizacion");
        layout.setHTML(0, 1, "Descripcion");
        layout.setHTML(0, 2, "Documento");

        addAutorizacion(layout, "012122", "Peritaje", "2010-0120-02");
        addAutorizacion(layout, "012122", "Valoracion de propiedad", "2010-0120-03");
        addAutorizacion(layout, "012122", "Venta del activo", "2010-0120-04");
        addAutorizacion(layout, "012122", "Cambio de ponente", "2010-0120-05");
        addAutorizacion(layout, "012122", "Restructuracion financiera", "2010-0120-06");

        HorizontalPanel buttonPanel = new HorizontalPanel();
        buttonPanel.setHorizontalAlignment(ALIGN_RIGHT);
        Button adicionar = new Button("Adicionar Autorizacion");
        adicionar.addClickHandler(new ClickHandler() {

            public void onClick(ClickEvent event) {
            }
        });
        buttonPanel.add(adicionar);
        layout.setWidget(layout.getRowCount(), 0, buttonPanel);
        cellFormatter.setColSpan(layout.getRowCount() - 1, 0, 3);

        VerticalPanel panel = new VerticalPanel();
        panel.add(layout);
        tab.add(panel, "Autorizaciones");
    }

    private void addPoliza(FlexTable layout, String tipoPoliza, String descripcion, String documentoAsociado, String fechaInicio, String fechaFin) {
        int row = layout.getRowCount();
        layout.setHTML(row, 0, tipoPoliza);
        layout.setWidget(row, 1, new Anchor(descripcion));
        layout.setWidget(row, 2, new DocumentSelector(documentoAsociado, false));
        layout.setHTML(row, 3, fechaInicio);
        layout.setHTML(row, 4, fechaFin);
    }

    private void panelAlarmas() {
        FlexTable table = new FlexTable();

        table.setCellSpacing(6);
        FlexCellFormatter cellFormatter = table.getFlexCellFormatter();

        int row = 0;
        table.setHTML(row, 0, "Role");
        table.setHTML(row, 1, "Inicia en");
        table.setHTML(row, 2, "Recurrente?");
        table.setHTML(row, 3, "Activa?");

        row++;
        table.setHTML(row, 0, "Coordinador");
        table.setHTML(row, 1, "2010-07-10");
        table.setHTML(row, 2, "No");
        CheckBox chk1 = new CheckBox();
        chk1.setValue(true);
        table.setWidget(row, 3, chk1);

        row++;
        table.setHTML(row, 0, "Ponente");
        table.setHTML(row, 1, "2010-07-05");
        table.setHTML(row, 2, "Si");
        CheckBox chk2 = new CheckBox();
        chk2.setValue(true);
        table.setWidget(row, 3, chk2);

        VerticalPanel panel = new VerticalPanel();
        panel.add(table);
        tab.add(panel, "Alarmas");
    }

    private void panelInformacionFinanciera() {
        FlexTable layout = new FlexTable();
        layout.setCellSpacing(6);
        FlexCellFormatter cellFormatter = layout.getFlexCellFormatter();

        int row = 0;
        layout.setHTML(row, 0, "Fecha de corte");
        layout.setWidget(row, 1, new DateBox());

        row++;
        layout.setHTML(row, 0, "Activos");
        layout.setWidget(row, 1, new TextBox());

        row++;
        layout.setHTML(row, 0, "Pasivos");
        layout.setWidget(row, 1, new TextBox());

        row++;
        layout.setHTML(row, 0, "Patrimonio");
        layout.setWidget(row, 1, new TextBox());

        row++;
        layout.setHTML(row, 0, "Ingresos Totales");
        layout.setWidget(row, 1, new TextBox());

        row++;
        layout.setHTML(row, 0, "Actividad Economica");
        row++;
        layout.setHTML(row, 0, "Revisión CIIU");
        TextBox textBox = new TextBox();
        textBox.setText("3AC");
        layout.setWidget(row, 1, textBox);

        row++;
        layout.setHTML(row, 0, "Descripción de CIIU");
        ListBox box = new ListBox();
        box.addItem("Fabricacion de prendas de vestir excepto prendas de piel");
        layout.setWidget(row, 1, box);

        row++;
        layout.setHTML(row, 0, "Empleos");
        row++;
        layout.setHTML(row, 0, "Directos");
        TextBox textBox2 = new TextBox();
        layout.setWidget(row, 1, textBox2);

        row++;
        layout.setHTML(row, 0, "Indirectos");
        layout.setWidget(row, 1, new TextBox());

        row++;
        layout.setHTML(row, 0, "Pensionados");
        layout.setWidget(row, 1, new TextBox());

        VerticalPanel panel = new VerticalPanel();
        panel.add(layout);
        tab.add(panel, "Informacion Financiera");
    }
}
