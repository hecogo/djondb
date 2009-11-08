package com.mxgraph.swing.examples;

import java.awt.BorderLayout;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.io.File;

import java.io.IOException;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JToolBar;
import javax.swing.SwingUtilities;

import com.mxgraph.canvas.mxGraphics2DCanvas;
import com.mxgraph.io.mxCodec;
import com.mxgraph.model.mxGraphModel;
import com.mxgraph.model.mxIGraphModel;
import com.mxgraph.swing.mxGraphComponent;
import com.mxgraph.swing.mxGraphOutline;
import com.mxgraph.swing.examples.editor.EditorMenuBar;
import com.mxgraph.swing.examples.editor.EditorPalette;
import com.mxgraph.swing.examples.editor.EditorPopupMenu;
import com.mxgraph.swing.examples.editor.EditorToolBar;
import com.mxgraph.swing.handler.mxKeyboardHandler;
import com.mxgraph.swing.handler.mxRubberband;
import com.mxgraph.swing.util.mxGraphActions;
import com.mxgraph.util.mxRectangle;
import com.mxgraph.util.mxResources;
import com.mxgraph.util.mxUndoManager;
import com.mxgraph.util.mxUndoableEdit;
import com.mxgraph.util.mxEventSource.mxEventListener;
import com.mxgraph.util.mxUtils;
import com.mxgraph.view.mxGraph;
import com.mxgraph.view.mxGraphView;
import javax.swing.JPanel;
import org.w3c.dom.Document;

public class BasicGraphEditor extends JPanel {

    /**
     * Adds required resources for i18n
     */
    static {
//        mxResources.add("/com/mxgraph/swing/examples/resources/editor");
    }
    /**
     * 
     */
    protected mxGraphComponent graphComponent;
    /**
     * 
     */
    protected mxGraphOutline graphOutline;
    /**
     * 
     */
    protected final EditorPalette shapesPalette,  imagesPalette,  symbolsPalette;
    /**
     * 
     */
    protected mxUndoManager undoManager;
    /**
     * 
     */
    protected String appTitle;
    /**
     * 
     */
    protected JLabel statusBar;
    /**
     * 
     */
    protected File currentFile;
    /**
     * 
     */
    protected boolean modified = false;
    /**
     * 
     */
    protected mxEventListener undoHandler = new mxEventListener() {

        public void invoke(Object source, Object[] args) {
            undoManager.undoableEditHappened((mxUndoableEdit) args[0]);
        }
    };
    /**
     * 
     */
    protected mxEventListener changeTracker = new mxEventListener() {

        public void invoke(Object source, Object[] args) {
            setModified(true);
        }
    };

    /**
     * 
     */
    public BasicGraphEditor(String appTitle, mxGraphComponent component) {
        // Stores a reference to the graph and creates the command history
        this.appTitle = appTitle;
        graphComponent = component;
        final mxGraph graph = graphComponent.getGraph();
        undoManager = new mxUndoManager();

        // Updates the modified flag if the graph model changes
        graph.getModel().addListener(mxIGraphModel.EVENT_CHANGE, changeTracker);

        // Adds the command history to the model and view
        graph.getModel().addListener(mxGraphModel.EVENT_UNDO, undoHandler);
        graph.getView().addListener(mxGraphView.EVENT_UNDO, undoHandler);

        // Keeps the selection in sync with the command history
        mxEventListener selectionHandler = new mxEventListener() {

            public void invoke(Object source, Object[] args) {
                graph.selectCellsForChanges(((mxUndoableEdit) args[0]).getChanges());
            }
        };

        undoManager.addListener(mxUndoManager.EVENT_UNDO, selectionHandler);
        undoManager.addListener(mxUndoManager.EVENT_REDO, selectionHandler);

        // Creates the graph outline component
        graphOutline = new mxGraphOutline(graphComponent);

        // Creates the library pane that contains the tabs with the palettes
        JTabbedPane libraryPane = new JTabbedPane();

        // Creates the symbols palette
        symbolsPalette = new EditorPalette();
        final JScrollPane symbolsScrollPane = new JScrollPane(symbolsPalette);
        symbolsScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        symbolsScrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        libraryPane.add("BPM", symbolsScrollPane);

        // Creates the shapes palette
        shapesPalette = new EditorPalette();
        final JScrollPane shapesScrollPane = new JScrollPane(shapesPalette);
        shapesScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        shapesScrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        libraryPane.add(mxResources.get("shapes"), shapesScrollPane);

        // Creates the images palette
        imagesPalette = new EditorPalette();
        final JScrollPane imagesScrollPane = new JScrollPane(imagesPalette);
        imagesScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        imagesScrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        libraryPane.add(mxResources.get("images"), imagesScrollPane);

        // Updates the widths of the palettes if the container size changes
        libraryPane.addComponentListener(new ComponentAdapter() {

            /**
             * 
             */
            public void componentResized(ComponentEvent e) {
                int w = shapesScrollPane.getWidth() - shapesScrollPane.getVerticalScrollBar().getWidth();
                shapesPalette.setPreferredWidth(w);

                w = imagesScrollPane.getWidth() - imagesScrollPane.getVerticalScrollBar().getWidth();
                imagesPalette.setPreferredWidth(w);

                w = symbolsScrollPane.getWidth() - symbolsScrollPane.getVerticalScrollBar().getWidth();
                symbolsPalette.setPreferredWidth(w);
            }
        });

        // Creates the inner split pane that contains the library with the
        // palettes and the graph outline on the left side of the window
        JSplitPane inner = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
                libraryPane, graphOutline);
        inner.setDividerLocation(320);
        inner.setResizeWeight(1);
        inner.setDividerSize(6);
        inner.setBorder(null);

        // Creates the outer split pane that contains the inner split pane and
        // the graph component on the right side of the window
        JSplitPane outer = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, inner,
                graphComponent);
        outer.setOneTouchExpandable(true);
        outer.setDividerLocation(200);
        outer.setDividerSize(6);
        outer.setBorder(null);

        // Creates the status bar
        statusBar = new JLabel(mxResources.get("ready"));
        statusBar.setBorder(BorderFactory.createEmptyBorder(2, 4, 2, 4));

        // Display some useful information about repaint events
        graph.addListener(mxGraph.EVENT_REPAINT, new mxEventListener() {

            public void invoke(Object source, Object[] args) {
                mxGraphics2DCanvas canvas = graphComponent.getControl().getCanvas();
                String buffer = (canvas != null && canvas.getImage() != null) ? ""
                        : " (unbuffered)";

                if (args.length == 0 || args[0] == null) {
                    status("Repaint all" + buffer);
                } else {
                    mxRectangle rect = (mxRectangle) args[0];
                    status("Repaint: x=" + (int) (rect.getX()) + " y=" + (int) (rect.getY()) + " w=" + (int) (rect.getWidth()) + " h=" + (int) (rect.getHeight()) + buffer);
                }
            }
        });

        // Puts everything together
        //setJMenuBar(new EditorMenuBar(this));
        setLayout(new BorderLayout());
        add(new EditorToolBar(this, JToolBar.HORIZONTAL),
                BorderLayout.NORTH);
        add(outer, BorderLayout.CENTER);
        add(statusBar, BorderLayout.SOUTH);

        // Installs rubberband selection and handling for some special
        // keystrokes such as F2, Control-C, -V, X, A etc.
        new mxRubberband(graphComponent);
        new mxKeyboardHandler(graphComponent);

        installListeners();
    }

    /**
     * 
     */
    protected void installListeners() {
        final mxGraph graph = graphComponent.getGraph();

        // Installs mouse wheel listener for zooming
        MouseWheelListener wheelTracker = new MouseWheelListener() {

            /**
             * 
             */
            public void mouseWheelMoved(MouseWheelEvent e) {
                mxGraphComponent graphComponent = BasicGraphEditor.this.getGraphComponent();

                if (e.getWheelRotation() < 0) {
                    graphComponent.zoomIn();
                } else {
                    graphComponent.zoomOut();
                }

                status(mxResources.get("scale") + ": " + (int) (100 * graph.getView().getScale()) + "%");
            }
        };

        graphOutline.addMouseWheelListener(wheelTracker);
        graphComponent.getControl().addMouseWheelListener(wheelTracker);

        // Installs the popup menu in the outline
        graphOutline.addMouseListener(new MouseAdapter() {

            /**
             * 
             */
            public void mousePressed(MouseEvent e) {
                // Handles context menu on the Mac where the trigger is on mousepressed
                mouseReleased(e);
            }

            /**
             * 
             */
            public void mouseReleased(MouseEvent e) {
                if (e.isPopupTrigger()) {
                    Point pt = SwingUtilities.convertPoint(e.getComponent(), e.getPoint(), graphComponent);
                    JCheckBoxMenuItem item = new JCheckBoxMenuItem(mxResources.get("wholePage"));
                    item.setSelected(graphOutline.isWholePage());

                    item.addActionListener(new ActionListener() {

                        /**
                         * 
                         */
                        public void actionPerformed(ActionEvent e) {
                            graphOutline.setWholePage(!graphOutline.isWholePage());
                            graphOutline.refresh(null);
                        }
                    });

                    JPopupMenu menu = new JPopupMenu();
                    menu.add(item);
                    menu.show(graphComponent, pt.x, pt.y);
                }
            }
        });

        // Installs the popup menu in the graph component
        graphComponent.getControl().addMouseListener(new MouseAdapter() {

            /**
             * 
             */
            public void mousePressed(MouseEvent e) {
                // Handles context menu on the Mac where the trigger is on mousepressed
                mouseReleased(e);
            }

            /**
             * 
             */
            public void mouseReleased(MouseEvent e) {
                if (e.isPopupTrigger()) {
                    Point pt = SwingUtilities.convertPoint(e.getComponent(), e.getPoint(), graphComponent);
                    EditorPopupMenu menu = new EditorPopupMenu(
                            BasicGraphEditor.this);
                    menu.show(graphComponent, pt.x, pt.y);
                }
            }
        });

        // Installs a mouse motion listener to display the mouse location
        graphComponent.getControl().addMouseMotionListener(
                new MouseMotionListener() {

                    /*
                     * (non-Javadoc)
                     * @see java.awt.event.MouseMotionListener#mouseDragged(java.awt.event.MouseEvent)
                     */
                    public void mouseDragged(MouseEvent e) {
                        status(e.getX() + ", " + e.getY());
                    }

                    /*
                     * (non-Javadoc)
                     * @see java.awt.event.MouseMotionListener#mouseMoved(java.awt.event.MouseEvent)
                     */
                    public void mouseMoved(MouseEvent e) {
                        mouseDragged(e);
                    }
                });
    }

    /**
     * 
     */
    public void setCurrentFile(File file) throws IOException {
        Document document = mxUtils.parse(mxUtils.readFile("/" + file.getPath()));

        if (document != null) {
            mxCodec codec = new mxCodec();
            mxGraph graph = this.graphComponent.getGraph();

            codec.decode(document.getDocumentElement(), graph.getModel());
        }
        setModified(false);

        File oldValue = currentFile;
        currentFile = file;

        firePropertyChange("currentFile", oldValue, file);
    }

    /**
     * 
     */
    public File getCurrentFile() {
        return currentFile;
    }

    /**
     * 
     * @param modified
     */
    public void setModified(boolean modified) {
        boolean oldValue = this.modified;
        this.modified = modified;

        firePropertyChange("modified", oldValue, modified);

    }

    /**
     * 
     * @return
     */
    public boolean isModified() {
        return modified;
    }

    /**
     * 
     */
    public mxGraphComponent getGraphComponent() {
        return graphComponent;
    }

    /**
     * 
     */
    public mxGraphOutline getGraphOutline() {
        return graphOutline;
    }

    /**
     * 
     */
    public mxUndoManager getUndoManager() {
        return undoManager;
    }

    /**
     * 
     * @param msg
     */
    public void status(String msg) {
        statusBar.setText(msg);
    }

    /**
     * 
     * @param name
     * @param action
     * @return
     */
    public Action bind(String name, final Action action) {
        return bind(name, action, null);
    }

    /**
     * 
     * @param name
     * @param action
     * @return
     */
    public Action bind(String name, final Action action, String iconUrl) {
        return new AbstractAction(name, (iconUrl != null) ? new ImageIcon(
                BasicGraphEditor.class.getResource(iconUrl)) : null) {

            public void actionPerformed(ActionEvent e) {
                action.actionPerformed(new ActionEvent(graphComponent, e.getID(), e.getActionCommand()));
            }
        };
    }

    /**
     * Placeholder for executing layouts in the commercial version. Layouts are
     * not shipped with the free version. This is overridden in the commercial
     * graph editor example.
     * 
     * @param key Key to be used for getting the label from mxResources and also
     * to create the layout instance for the commercial graph editor example.
     * @return
     */
    public Action graphLayout(final String key) {
        return new AbstractAction(mxResources.get(key)) {

            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(graphComponent, mxResources.get("noLayouts"));
            }
        };
    }
}
