/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.HasHorizontalAlignment;
import com.google.gwt.user.client.ui.HasHorizontalAlignment.HorizontalAlignmentConstant;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.VerticalPanel;

/**
 * Main entry point.
 *
 * @author cross
 */
public class testEntryPoint implements EntryPoint {

    /**
     * Creates a new instance of testEntryPoint
     */
    public testEntryPoint() {
    }

    /** 
     * The entry point method, called automatically by loading a module
     * that declares an implementing class as an entry-point
     */
    public void onModuleLoad() {
        VerticalPanel vpanel = new VerticalPanel();
        vpanel.setSpacing(8);
        HTML html = new HTML("<embed src=\"http://www.supersociedades.gov.co/web/estructura/banner_super_130.swf\" quality=\"high\" pluginspage=\"http://www.adobe.com/go/getflashplayer\" play=\"true\" loop=\"true\" scale=\"showall\" wmode=\"window\" devicefont=\"false\" bgcolor=\"#ffffff\" name=\"banner_super\" menu=\"true\" allowfullscreen=\"false\" allowscriptaccess=\"sameDomain\" salign=\"\" type=\"application/x-shockwave-flash\" align=\"middle\" height=\"130\" width=\"800\">");
        html.setHeight("160px");
        vpanel.add(html);

        HorizontalPanel panel = new HorizontalPanel();
        vpanel.add(panel);

        VerticalPanel reciclable = new VerticalPanel();

        Menu menu = new Menu(reciclable);
        panel.add(menu);

        /*
        PanelPrincipal panelPrincipal = new PanelPrincipal();
        panelPrincipal.setWidth("500px");
        panelPrincipal.setHeight("600px");

        panel.add(panelPrincipal);
         */

        ListaProcesos lista = new ListaProcesos(reciclable, TIPOPANEL.MODIFICACION);
        reciclable.add(lista);
        lista.setWidth("500px");
        lista.setHeight("600px");
        panel.add(reciclable);
        RootPanel.get().add(vpanel);
    }
}
