/*
 * $Id: EditorActions.java,v 1.3 2008/10/08 11:22:24 gaudenz Exp $
 * Copyright (c) 2001-2005, Gaudenz Alder
 * 
 * All rights reserved.
 * 
 * See LICENSE file for license details. If you are unable to locate
 * this file please contact info (at) jgraph (dot) com.
 */
package com.mxgraph.swing.examples.editor;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.awt.print.PageFormat;
import java.awt.print.Paper;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Method;
import java.util.HashSet;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JColorChooser;
import javax.swing.JEditorPane;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JSplitPane;
import javax.swing.SwingUtilities;
import javax.swing.filechooser.FileFilter;
import javax.swing.text.html.HTML;
import javax.swing.text.html.HTMLDocument;
import javax.swing.text.html.HTMLEditorKit;

import org.w3c.dom.Document;

import com.mxgraph.algebra.mxDistanceCostFunction;
import com.mxgraph.algebra.mxGraphAlgebra;
import com.mxgraph.io.mxCodec;
import com.mxgraph.model.mxCell;
import com.mxgraph.model.mxIGraphModel;
import com.mxgraph.renderer.mxHtmlCellRenderer;
import com.mxgraph.renderer.mxSvgCellRenderer;
import com.mxgraph.renderer.mxVmlCellRenderer;
import com.mxgraph.swing.mxGraphComponent;
import com.mxgraph.swing.mxGraphOutline;
import com.mxgraph.swing.examples.BasicGraphEditor;
import com.mxgraph.swing.examples.FreeGraphEditor;
import com.mxgraph.swing.examples.FreeGraphEditor.CustomGraphComponent;
import com.mxgraph.swing.handler.mxConnectionHandler;
import com.mxgraph.swing.util.mxGraphActions;
import com.mxgraph.swing.view.mxCellEditor;
import com.mxgraph.swing.view.mxGraphComponentCellRenderer;
import com.mxgraph.util.mxConstants;
import com.mxgraph.util.mxResources;
import com.mxgraph.util.mxUtils;
import com.mxgraph.view.mxGraph;
import javax.swing.JPanel;

/**
 * @author Administrator
 * 
 */
public class EditorActions {

    /**
     *
     */
    public static class ToggleRulersItem extends JCheckBoxMenuItem {

        /**
         * 
         */
        public ToggleRulersItem(final BasicGraphEditor frame, String name) {
            super(name);
            setSelected(frame.getGraphComponent().getColumnHeader() != null);

            addActionListener(new ActionListener() {

                /**
                 * 
                 */
                public void actionPerformed(ActionEvent e) {
                    if (frame instanceof BasicGraphEditor) {
                        mxGraphComponent graphComponent = frame.getGraphComponent();
                        if (graphComponent.getColumnHeader() != null) {
                            graphComponent.setColumnHeader(null);
                            graphComponent.setRowHeader(null);
                        } else {
                            graphComponent.setColumnHeaderView(new EditorRuler(
                                    graphComponent,
                                    EditorRuler.ORIENTATION_HORIZONTAL));
                            graphComponent.setRowHeaderView(new EditorRuler(
                                    graphComponent,
                                    EditorRuler.ORIENTATION_VERTICAL));
                        }
                    }
                }
            });
        }
    }

    /**
     *
     */
    public static class ToggleGridItem extends JCheckBoxMenuItem {

        /**
         * 
         */
        public ToggleGridItem(final BasicGraphEditor frame, String name) {
            super(name);
            setSelected(true);

            addActionListener(new ActionListener() {

                /**
                 * 
                 */
                public void actionPerformed(ActionEvent e) {
                    mxGraphComponent graphComponent = frame.getGraphComponent();
                    mxGraph graph = graphComponent.getGraph();

                    if (graph != null) {
                        boolean enabled = !graph.isGridEnabled();

                        graph.setGridEnabled(enabled);
                        graphComponent.setGridVisible(enabled);
                        graphComponent.repaint();
                        setSelected(enabled);
                    }
                }
            });
        }
    }

    /**
     *
     */
    public static class ToggleOutlineItem extends JCheckBoxMenuItem {

        /**
         * 
         */
        public ToggleOutlineItem(final BasicGraphEditor frame, String name) {
            super(name);
            setSelected(true);

            addActionListener(new ActionListener() {

                /**
                 * 
                 */
                public void actionPerformed(ActionEvent e) {
                    if (frame instanceof BasicGraphEditor) {
                        final mxGraphOutline outline = frame.getGraphOutline();
                        outline.setVisible(!outline.isVisible());
                        outline.revalidate();

                        SwingUtilities.invokeLater(new Runnable() {
                            /*
                             * (non-Javadoc)
                             * @see java.lang.Runnable#run()
                             */

                            public void run() {
                                if (outline.getParent() instanceof JSplitPane) {
                                    if (outline.isVisible()) {
                                        ((JSplitPane) outline.getParent()).setDividerLocation(frame.getHeight() - 300);
                                        ((JSplitPane) outline.getParent()).setDividerSize(6);
                                    } else {
                                        ((JSplitPane) outline.getParent()).setDividerSize(0);
                                    }
                                }
                            }
                        });
                    }
                }
            });
        }
    }

    /**
     *
     */
    public static class ExitAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());
            frame.dispose();
        }
    }

    /**
     *
     */
    public static class StylesheetAction extends AbstractAction {

        /**
         * 
         */
        protected String stylesheet;

        /**
         * 
         */
        public StylesheetAction(String stylesheet) {
            this.stylesheet = stylesheet;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null) {
                mxCodec codec = new mxCodec();
                Document doc = mxUtils.loadDocument(EditorActions.class.getResource(stylesheet).toString());

                if (doc != null) {
                    codec.decode(doc.getDocumentElement(), graph.getStylesheet());
                    graph.refresh();
                }
            }
        }
    }

    /**
     *
     */
    public static class ZoomPolicyAction extends AbstractAction {

        /**
         * 
         */
        protected int zoomPolicy;

        /**
         * 
         */
        public ZoomPolicyAction(int zoomPolicy) {
            this.zoomPolicy = zoomPolicy;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                graphComponent.setPageVisible(true);
                graphComponent.setZoomPolicy(zoomPolicy);
            }
        }
    }

    /**
     *
     */
    public static class GridStyleAction extends AbstractAction {

        /**
         * 
         */
        protected int style;

        /**
         * 
         */
        public GridStyleAction(int style) {
            this.style = style;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                graphComponent.setGridStyle(style);
                graphComponent.repaint();
            }
        }
    }

    /**
     *
     */
    public static class GridColorAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());
                mxGraph graph = graphComponent.getGraph();

                if (graph != null) {
                    Color newColor = JColorChooser.showDialog(frame,
                            mxResources.get("gridColor"), graphComponent.getGridColor());

                    if (newColor != null) {
                        graphComponent.setGridColor(newColor);
                        graphComponent.repaint();
                    }
                }
            }
        }
    }

    /**
     *
     */
    public static class ScaleAction extends AbstractAction {

        /**
         * 
         */
        protected double scale;

        /**
         * 
         */
        public ScaleAction(double scale) {
            this.scale = scale;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                mxGraph graph = graphComponent.getGraph();

                if (graph != null) {
                    double scale = this.scale;

                    if (scale == 0) {
                        JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());

                        String value = (String) JOptionPane.showInputDialog(
                                frame, mxResources.get("value"), mxResources.get("scale") + " (%)", JOptionPane.PLAIN_MESSAGE,
                                null, null, "");

                        if (value != null) {
                            scale = Double.parseDouble(value.replace("%", "")) / 100;
                        }
                    }

                    if (scale > 0) {
                        graphComponent.zoomTo(scale, graphComponent.isCenterZoom());
                    }
                }
            }
        }
    }

    /**
     *
     */
    public static class PageSetupAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                PrinterJob pj = PrinterJob.getPrinterJob();

                PageFormat format = pj.pageDialog(graphComponent.getPageFormat());

                if (format != null) {
                    graphComponent.setPageFormat(format);
                    graphComponent.zoomAndCenter();
                }
            }
        }
    }

    /**
     *
     */
    public static class PrintAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                PrinterJob pj = PrinterJob.getPrinterJob();

                if (pj.printDialog()) {
                    PageFormat pf = pj.defaultPage();
                    Paper paper = new Paper();
                    double margin = 36;
                    paper.setImageableArea(margin, margin, paper.getWidth() - margin * 2, paper.getHeight() - margin * 2);
                    pf.setPaper(paper);
                    pj.setPrintable(graphComponent, pf);

                    try {
                        pj.print();
                    } catch (PrinterException e2) {
                        System.out.println(e2);
                    }
                }
            }
        }
    }

    /**
     *
     */
    public static class SaveAction extends AbstractAction {

        /**
         * 
         */
        protected boolean showDialog;
        /**
         * 
         */
        protected String lastDir = null;

        /**
         * 
         */
        public SaveAction(boolean showDialog) {
            this.showDialog = showDialog;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof FreeGraphEditor.CustomGraphComponent) {
                try {
                    FreeGraphEditor editor = (FreeGraphEditor) ((FreeGraphEditor.CustomGraphComponent) e.getSource()).getParent().getParent();
                    editor.save();
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
            } else {
                return;
            }
            ;
        }
    }

    /**
     *
     */
    public static class SelectShortestPathAction extends AbstractAction {

        /**
         * 
         */
        protected boolean directed;

        /**
         * 
         */
        public SelectShortestPathAction(boolean directed) {
            this.directed = directed;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                mxGraph graph = graphComponent.getGraph();
                mxIGraphModel model = graph.getModel();

                Object source = null;
                Object target = null;

                Object[] cells = graph.getSelectionCells();

                for (int i = 0; i < cells.length; i++) {
                    if (model.isVertex(cells[i])) {
                        if (source == null) {
                            source = cells[i];
                        } else if (target == null) {
                            target = cells[i];
                        }
                    }

                    if (source != null && target != null) {
                        break;
                    }
                }

                if (source != null && target != null) {
                    int steps = graph.getChildEdges(graph.getDefaultParent()).length;
                    Object[] path = mxGraphAlgebra.getInstance().getShortestPath(graph, source, target,
                            new mxDistanceCostFunction(), steps,
                            directed);
                    graph.setSelectionCells(path);
                } else {
                    JOptionPane.showMessageDialog(graphComponent, mxResources.get("noSourceAndTargetSelected"));
                }
            }
        }
    }

    /**
     *
     */
    public static class SelectSpanningTreeAction extends AbstractAction {

        /**
         * 
         */
        protected boolean directed;

        /**
         * 
         */
        public SelectSpanningTreeAction(boolean directed) {
            this.directed = directed;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                mxGraph graph = graphComponent.getGraph();
                mxIGraphModel model = graph.getModel();

                Object parent = graph.getDefaultParent();
                Object[] cells = graph.getSelectionCells();

                for (int i = 0; i < cells.length; i++) {
                    if (model.getChildCount(cells[i]) > 0) {
                        parent = cells[i];
                        break;
                    }
                }

                Object[] v = graph.getChildVertices(parent);
                Object[] mst = mxGraphAlgebra.getInstance().getMinimumSpanningTree(graph, v,
                        new mxDistanceCostFunction(), directed);
                graph.setSelectionCells(mst);
            }
        }
    }

    /**
     *
     */
    public static class ToggleDirtyAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                graphComponent.showDirtyRectangle = !graphComponent.showDirtyRectangle;
            }
        }
    }

    /**
     *
     */
    public static class ToggleImagePreviewAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                graphComponent.getGraphHandler().setImagePreview(
                        !graphComponent.getGraphHandler().isImagePreview());
            }
        }
    }

    /**
     *
     */
    public static class ToggleConnectModeAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                mxConnectionHandler handler = graphComponent.getConnectionHandler();
                handler.setHandleEnabled(!handler.isHandleEnabled());
            }
        }
    }

    /**
     *
     */
    public static class ToggleCreateTargetItem extends JCheckBoxMenuItem {

        /**
         * 
         */
        public ToggleCreateTargetItem(final BasicGraphEditor frame, String name) {
            super(name);
            setSelected(true);

            addActionListener(new ActionListener() {

                /**
                 * 
                 */
                public void actionPerformed(ActionEvent e) {
                    mxGraphComponent graphComponent = frame.getGraphComponent();

                    if (graphComponent != null) {
                        mxConnectionHandler handler = graphComponent.getConnectionHandler();
                        handler.setCreateTarget(!handler.isCreateTarget());
                        setSelected(handler.isCreateTarget());
                    }
                }
            });
        }
    }

    /**
     *
     */
    public static class PromptPropertyAction extends AbstractAction {

        /**
         * 
         */
        protected Object target;
        /**
         * 
         */
        protected String fieldname,  message;

        /**
         * 
         */
        public PromptPropertyAction(Object target, String message) {
            this(target, message, message);
        }

        /**
         * 
         */
        public PromptPropertyAction(Object target, String message,
                String fieldname) {
            this.target = target;
            this.message = message;
            this.fieldname = fieldname;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());

            try {
                Method getter = target.getClass().getMethod("get" + fieldname);
                Object current = getter.invoke(target);

                // TODO: Support other atomic types
                if (current instanceof Integer) {
                    Method setter = target.getClass().getMethod(
                            "set" + fieldname, new Class[]{int.class});

                    String value = (String) JOptionPane.showInputDialog(frame,
                            "Value", message, JOptionPane.PLAIN_MESSAGE, null,
                            null, current);

                    if (value != null) {
                        setter.invoke(target, Integer.parseInt(value));
                    }
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }

            // Repaints the graph component
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                graphComponent.repaint();
            }
        }
    }

    /**
     *
     */
    public static class TogglePropertyItem extends JCheckBoxMenuItem {

        /**
         * 
         */
        public TogglePropertyItem(Object target, String name, String fieldname) {
            this(target, name, fieldname, false);
        }

        /**
         * 
         */
        public TogglePropertyItem(Object target, String name, String fieldname,
                boolean refresh) {
            this(target, name, fieldname, refresh, null);
        }

        /**
         * 
         */
        public TogglePropertyItem(final Object target, String name,
                final String fieldname, final boolean refresh,
                ActionListener listener) {
            super(name);

            // Since action listeners are processed last to first we add the given
            // listener here which means it will be processed after the one below
            if (listener != null) {
                addActionListener(listener);
            }

            addActionListener(new ActionListener() {

                /**
                 * 
                 */
                public void actionPerformed(ActionEvent e) {
                    execute(target, fieldname, refresh);
                }
            });

            PropertyChangeListener propertyChangeListener = new PropertyChangeListener() {

                /*
                 * (non-Javadoc)
                 * @see java.beans.PropertyChangeListener#propertyChange(java.beans.PropertyChangeEvent)
                 */
                public void propertyChange(PropertyChangeEvent evt) {
                    if (evt.getPropertyName().equalsIgnoreCase(fieldname)) {
                        update(target, fieldname);
                    }
                }
            };

            if (target instanceof mxGraphComponent) {
                ((mxGraphComponent) target).addPropertyChangeListener(propertyChangeListener);
            } else if (target instanceof mxGraph) {
                ((mxGraph) target).addPropertyChangeListener(propertyChangeListener);
            }

            update(target, fieldname);
        }

        /**
         * 
         */
        public void update(Object target, String fieldname) {
            try {
                Method getter = target.getClass().getMethod("is" + fieldname);
                Object current = getter.invoke(target);

                if (current instanceof Boolean) {
                    setSelected(((Boolean) current).booleanValue());
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        /**
         * 
         */
        public void execute(Object target, String fieldname, boolean refresh) {
            try {
                Method getter = target.getClass().getMethod("is" + fieldname);
                Method setter = target.getClass().getMethod("set" + fieldname,
                        new Class[]{boolean.class});

                Object current = getter.invoke(target);

                if (current instanceof Boolean) {
                    boolean value = !((Boolean) current).booleanValue();
                    setter.invoke(target, value);
                    setSelected(value);
                }

                if (refresh) {
                    mxGraph graph = null;

                    if (target instanceof mxGraph) {
                        graph = (mxGraph) target;
                    } else if (target instanceof mxGraphComponent) {
                        graph = ((mxGraphComponent) target).getGraph();
                    }

                    graph.refresh();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    /**
     *
     */
    public static class RedoAction extends AbstractAction {

        /**
         * 
         */
        protected BasicGraphEditor frame;

        /**
         * 
         */
        public RedoAction(BasicGraphEditor frame) {
            this.frame = frame;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            frame.getUndoManager().redo();
        }
    }

    /**
     *
     */
    public static class UndoAction extends AbstractAction {

        /**
         * 
         */
        protected BasicGraphEditor frame;

        /**
         * 
         */
        public UndoAction(BasicGraphEditor frame) {
            this.frame = frame;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            frame.getUndoManager().undo();
        }
    }

    /**
     *
     */
    public static class FontStyleAction extends AbstractAction {

        /**
         * 
         */
        protected boolean bold;

        /**
         * 
         */
        public FontStyleAction(boolean bold) {
            this.bold = bold;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                Component editorComponent = null;

                if (graphComponent.getCellEditor() instanceof mxCellEditor) {
                    editorComponent = ((mxCellEditor) graphComponent.getCellEditor()).getEditor();
                }

                if (editorComponent instanceof JEditorPane) {
                    JEditorPane editorPane = (JEditorPane) editorComponent;
                    int start = editorPane.getSelectionStart();
                    int ende = editorPane.getSelectionEnd();
                    String text = editorPane.getSelectedText();

                    if (text == null) {
                        text = "";
                    }

                    try {
                        HTMLEditorKit editorKit = new HTMLEditorKit();
                        HTMLDocument document = (HTMLDocument) editorPane.getDocument();
                        document.remove(start, (ende - start));
                        editorKit.insertHTML(document, start, ((bold) ? "<b>"
                                : "<i>") + text + ((bold) ? "</b>" : "</i>"), 0, 0,
                                (bold) ? HTML.Tag.B : HTML.Tag.I);
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }

                    editorPane.requestFocus();
                    editorPane.select(start, ende);
                } else {
                    mxIGraphModel model = graphComponent.getGraph().getModel();
                    model.beginUpdate();
                    try {
                        graphComponent.stopEditing(false);
                        graphComponent.getGraph().toggleCellStyleFlags(
                                mxConstants.STYLE_FONTSTYLE,
                                (bold) ? mxConstants.FONT_BOLD
                                : mxConstants.FONT_ITALIC);
                    } finally {
                        model.endUpdate();
                    }
                }
            }
        }
    }

    /**
     *
     */
    public static class WarningAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                Object[] cells = graphComponent.getGraph().getSelectionCells();

                if (cells != null && cells.length > 0) {
                    String warning = JOptionPane.showInputDialog(mxResources.get("enterWarningMessage"));

                    for (int i = 0; i < cells.length; i++) {
                        graphComponent.setWarning(cells[i], warning);
                    }
                } else {
                    JOptionPane.showMessageDialog(graphComponent, mxResources.get("noCellSelected"));
                }
            }
        }
    }

    /**
     *
     */
    public static class ToggleAction extends AbstractAction {

        /**
         * 
         */
        protected String key;
        /**
         * 
         */
        protected boolean defaultValue;

        /**
         * 
         * @param key
         */
        public ToggleAction(String key) {
            this(key, false);
        }

        /**
         * 
         * @param key
         */
        public ToggleAction(String key, boolean defaultValue) {
            this.key = key;
            this.defaultValue = defaultValue;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null) {
                graph.toggleCellStyles(key, defaultValue);
            }
        }
    }

    /**
     *
     */
    public static class SetStyleAction extends AbstractAction {

        /**
         * 
         */
        protected String value;

        /**
         * 
         * @param key
         */
        public SetStyleAction(String value) {
            this.value = value;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null && !graph.isSelectionEmpty()) {
                graph.setCellStyle(value);
            }
        }
    }

    /**
     *
     */
    public static class KeyValueAction extends AbstractAction {

        /**
         * 
         */
        protected String key,  value;

        /**
         * 
         * @param key
         */
        public KeyValueAction(String key) {
            this(key, null);
        }

        /**
         * 
         * @param key
         */
        public KeyValueAction(String key, String value) {
            this.key = key;
            this.value = value;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null && !graph.isSelectionEmpty()) {
                graph.setCellStyles(key, value);
            }
        }
    }

    /**
     *
     */
    public static class PromptValueAction extends AbstractAction {

        /**
         * 
         */
        protected String key,  message;

        /**
         * 
         * @param key
         */
        public PromptValueAction(String key, String message) {
            this.key = key;
            this.message = message;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null && !graph.isSelectionEmpty()) {
                JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());

                String value = (String) JOptionPane.showInputDialog(frame,
                        mxResources.get("value"), message,
                        JOptionPane.PLAIN_MESSAGE, null, null, "");

                if (value != null) {
                    if (value.equals("none")) {
                        value = null;
                    }

                    graph.setCellStyles(key, value);
                }
            }
        }
    }

    /**
     *
     */
    public static class AlignCellsAction extends AbstractAction {

        /**
         * 
         */
        protected String align;

        /**
         * 
         * @param key
         */
        public AlignCellsAction(String align) {
            this.align = align;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null && !graph.isSelectionEmpty()) {
                graph.alignCells(align);
            }
        }
    }

    /**
     *
     */
    public static class AutosizeAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null && !graph.isSelectionEmpty()) {
                graph.updateSize(graph.getSelectionCell());
            }
        }
    }

    /**
     *
     */
    public static class ColorAction extends AbstractAction {

        /**
         * 
         */
        protected String name,  key;

        /**
         * 
         * @param key
         */
        public ColorAction(String name, String key) {
            this.name = name;
            this.key = key;
        }

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null && !graph.isSelectionEmpty()) {
                JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());
                Color newColor = JColorChooser.showDialog(frame, name, null);

                if (newColor != null) {
                    graph.setCellStyles(key, mxUtils.hexString(newColor));
                }
            }
        }
    }

    /**
     *
     */
    public static class BackgroundImageAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());

                String value = (String) JOptionPane.showInputDialog(frame,
                        mxResources.get("backgroundImage"), "URL",
                        JOptionPane.PLAIN_MESSAGE, null, null,
                        "http://www.callatecs.com/images/background2.JPG");

                if (value != null) {
                    mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();

                    if (value.length() == 0) {
                        graphComponent.setBackgroundImage(null);
                    } else {
                        graphComponent.setBackgroundImage(new ImageIcon(mxUtils.loadImage(value)));
                    }

                    // Forces a repaint of the outline
                    graphComponent.getGraph().repaint();
                }
            }
        }
    }

    /**
     *
     */
    public static class BackgroundAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                JFrame frame = (JFrame) SwingUtilities.windowForComponent(graphComponent);
                Color newColor = JColorChooser.showDialog(frame, mxResources.get("background"), null);

                if (newColor != null) {
                    graphComponent.getViewport().setOpaque(false);
                    graphComponent.setBackground(newColor);
                }

                // Forces a repaint of the outline
                graphComponent.getGraph().repaint();
            }
        }
    }

    /**
     *
     */
    public static class PageBackgroundAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() instanceof mxGraphComponent) {
                mxGraphComponent graphComponent = (mxGraphComponent) e.getSource();
                JFrame frame = (JFrame) SwingUtilities.windowForComponent(graphComponent);
                Color newColor = JColorChooser.showDialog(frame, mxResources.get("pageBackground"), null);

                if (newColor != null) {
                    graphComponent.setPageBackgroundColor(newColor);
                }

                // Forces a repaint of the component
                graphComponent.repaint();
            }
        }
    }

    /**
     *
     */
    public static class StyleAction extends AbstractAction {

        /**
         * 
         */
        public void actionPerformed(ActionEvent e) {
            mxGraph graph = mxGraphActions.getGraph(e);

            if (graph != null && !graph.isSelectionEmpty()) {
                JFrame frame = (JFrame) SwingUtilities.windowForComponent((Component) e.getSource());

                String initial = graph.getModel().getStyle(
                        graph.getSelectionCell());
                String value = (String) JOptionPane.showInputDialog(frame,
                        mxResources.get("style"), mxResources.get("style"),
                        JOptionPane.PLAIN_MESSAGE, null, null, initial);

                if (value != null) {
                    graph.setCellStyle(value);
                }
            }
        }
    }
}
