package com.mxgraph.swing.examples;

import java.awt.Color;
import java.awt.Point;
import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URL;
import java.text.NumberFormat;
import java.util.Iterator;
import java.util.List;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.UIManager;

import org.w3c.dom.Document;

import com.mxgraph.io.mxCodec;
import com.mxgraph.model.mxCell;
import com.mxgraph.model.mxGeometry;
import com.mxgraph.model.mxICell;
import com.mxgraph.model.mxIGraphModel;
import com.mxgraph.swing.mxGraphComponent;
import com.mxgraph.swing.examples.editor.EditorPalette;
import com.mxgraph.swing.util.mxGraphTransferable;
import com.mxgraph.util.mxConstants;
import com.mxgraph.util.mxPoint;
import com.mxgraph.util.mxUtils;
import com.mxgraph.util.mxEventSource.mxEventListener;
import com.mxgraph.view.mxCellState;
import com.mxgraph.view.mxGraph;
import java.net.URI;
import java.util.ResourceBundle;

public class FreeGraphEditor extends BasicGraphEditor {

    /**
     * Holds the shared number formatter.
     * 
     * @see NumberFormat#getInstance()
     */
    public static final NumberFormat numberFormat = NumberFormat.getInstance();
    /**
     * Holds the URL for the icon to be used as a handle for creating new
     * connections. This is currently unused.
     */
    public static URL url = null;

    //FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/connector.gif");
    /**
     * 
     */
    public FreeGraphEditor() {
        super("mxGraph Editor", new CustomGraphComponent(new CustomGraph()));
        final mxGraph graph = graphComponent.getGraph();

        // Sets the edge template to be used for creating new edges if an edge
        // is clicked in the shape palette
        shapesPalette.addListener(EditorPalette.EVENT_SELECT, new mxEventListener() {

            public void invoke(Object sender, Object[] args) {
                if (args != null && args.length > 0 && args[1] instanceof mxGraphTransferable) {
                    mxGraphTransferable t = (mxGraphTransferable) args[1];
                    Object cell = t.getCells()[0];

                    if (graph.getModel().isEdge(cell)) {
                        ((CustomGraph) graph).setEdgeTemplate(cell);
                    }
                }
            }
        });

        // Adds some template cells for dropping into the graph
        shapesPalette.addTemplate(
                "Container",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/swimlane.png")),
                "swimlane", 180, 200, "Container");
        shapesPalette.addTemplate(
                "Rectangle",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/rectangle.png")),
                null, 160, 120, "");
        shapesPalette.addTemplate(
                "Rounded Rectangle",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/rounded.png")),
                "rounded=1", 160, 120, "");
        shapesPalette.addTemplate(
                "Ellipse",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/ellipse.png")),
                "ellipse", 160, 160, "");
        shapesPalette.addTemplate(
                "Double Ellipse",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/doubleellipse.png")),
                "ellipse;shape=doubleEllipse", 160, 160, "");
        shapesPalette.addTemplate(
                "Triangle",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/triangle.png")),
                "triangle", 120, 160, "");
        shapesPalette.addTemplate(
                "Rhombus",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/rhombus.png")),
                "rhombus", 160, 160, "");
        shapesPalette.addTemplate(
                "Horizontal Line",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/hline.png")),
                "line", 160, 10, "");
        shapesPalette.addTemplate(
                "Hexagon",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/hexagon.png")),
                "shape=hexagon", 160, 120, "");
        shapesPalette.addTemplate(
                "Cylinder",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/cylinder.png")),
                "shape=cylinder", 120, 160, "");
        shapesPalette.addTemplate("Actor", new ImageIcon(FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/actor.png")),
                "shape=actor", 120, 160, "");
        shapesPalette.addTemplate("Cloud", new ImageIcon(FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/cloud.png")),
                "ellipse;shape=cloud", 160, 120, "");

        shapesPalette.addEdgeTemplate(
                "Straight",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/straight.png")),
                "straight", 120, 120, "");
        shapesPalette.addEdgeTemplate(
                "Horizontal Connector",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/connect.png")),
                null, 100, 100, "");
        shapesPalette.addEdgeTemplate(
                "Vertical Connector",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/vertical.png")),
                "vertical", 100, 100, "");
        shapesPalette.addEdgeTemplate(
                "Entity Relation",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/entity.png")),
                "entity", 100, 100, "");
        shapesPalette.addEdgeTemplate(
                "Arrow",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/arrow.png")),
                "arrow", 120, 120, "");

        imagesPalette.addTemplate("Bell", new ImageIcon(FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/bell.png")),
                "image;image=/com/mxgraph/swing/examples/images/bell.png", 50,
                50, "Bell");
        imagesPalette.addTemplate("Box", new ImageIcon(FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/box.png")),
                "image;image=/com/mxgraph/swing/examples/images/box.png", 50,
                50, "Box");
        imagesPalette.addTemplate(
                "Cube",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/cube_green.png")),
                "image;image=/com/mxgraph/swing/examples/images/cube_green.png",
                50, 50, "Cube");
        imagesPalette.addTemplate(
                "User",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/dude3.png")),
                "roundImage;image=/com/mxgraph/swing/examples/images/dude3.png",
                50, 50, "User");
        imagesPalette.addTemplate(
                "Earth",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/earth.png")),
                "roundImage;image=/com/mxgraph/swing/examples/images/earth.png",
                50, 50, "Earth");
        imagesPalette.addTemplate("Gear", new ImageIcon(FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/gear.png")),
                "roundImage;image=/com/mxgraph/swing/examples/images/gear.png",
                50, 50, "Gear");
        imagesPalette.addTemplate("Home", new ImageIcon(FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/house.png")),
                "image;image=/com/mxgraph/swing/examples/images/house.png", 50,
                50, "Home");
        imagesPalette.addTemplate(
                "Package",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/package.png")),
                "image;image=/com/mxgraph/swing/examples/images/package.png",
                50, 50, "Package");
        imagesPalette.addTemplate(
                "Printer",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/printer.png")),
                "image;image=/com/mxgraph/swing/examples/images/printer.png",
                50, 50, "Printer");
        imagesPalette.addTemplate("Server", new ImageIcon(FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/server.png")),
                "image;image=/com/mxgraph/swing/examples/images/server.png",
                50, 50, "Server");
        imagesPalette.addTemplate(
                "Workplace",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/workplace.png")),
                "image;image=/com/mxgraph/swing/examples/images/workplace.png",
                50, 50, "Workplace");
        imagesPalette.addTemplate(
                "Wrench",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/wrench.png")),
                "roundImage;image=/com/mxgraph/swing/examples/images/wrench.png",
                50, 50, "Wrench");

        symbolsPalette.addTemplate(
                "Cancel",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/cancel_end.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/cancel_end.png",
                80, 80, "Cancel");
        symbolsPalette.addTemplate(
                "Error",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/error.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/error.png",
                80, 80, "Error");
        symbolsPalette.addTemplate(
                "Event",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/event.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/event.png",
                80, 80, "Event");
        symbolsPalette.addTemplate(
                "Fork",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/fork.png")),
                "rhombusSymbol;image=/com/mxgraph/swing/examples/images/fork.png",
                80, 80, "Fork");
        symbolsPalette.addTemplate(
                "Inclusive",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/inclusive.png")),
                "rhombusSymbol;image=/com/mxgraph/swing/examples/images/inclusive.png",
                80, 80, "Inclusive");
        symbolsPalette.addTemplate(
                "Link",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/link.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/link.png",
                80, 80, "Link");
        symbolsPalette.addTemplate(
                "Merge",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/merge.png")),
                "rhombusSymbol;image=/com/mxgraph/swing/examples/images/merge.png",
                80, 80, "Merge");
        symbolsPalette.addTemplate(
                "Message",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/message.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/message.png",
                80, 80, "Message");
        symbolsPalette.addTemplate(
                "Multiple",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/multiple.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/multiple.png",
                80, 80, "Multiple");
        symbolsPalette.addTemplate(
                "Rule",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/rule.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/rule.png",
                80, 80, "Rule");
        symbolsPalette.addTemplate(
                "Terminate",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/terminate.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/terminate.png",
                80, 80, "Terminate");
        symbolsPalette.addTemplate(
                "Timer",
                new ImageIcon(
                FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/images/timer.png")),
                "roundSymbol;image=/com/mxgraph/swing/examples/images/timer.png",
                80, 80, "Timer");
    }

    public void save() throws IOException {
        mxCodec codec = new mxCodec();
        mxGraph graph = this.graphComponent.getGraph();
        String xml = mxUtils.getXml(codec.encode(graph.getModel()));

        mxUtils.writeFile(xml, "/" + getCurrentFile().getPath());
    }
    /**
     * 
     */
    public static class CustomGraphComponent extends mxGraphComponent {

        /**
         * 
         * @param graph
         */
        public CustomGraphComponent(mxGraph graph) {
            super(graph);

            // Sets switches typically used in an editor
            setPageVisible(true);
            setGridVisible(true);
            setAntiAlias(false);
            setToolTips(true);
            setCenterZoom(false);
            getConnectionHandler().setCreateTarget(true);

            // Loads the defalt stylesheet from an external file
            mxCodec codec = new mxCodec();

            String style = FreeGraphEditor.class.getResource("/com/mxgraph/swing/examples/resources/default-style.xml").toString();
            Document doc = mxUtils.loadDocument(style);
            codec.decode(doc.getDocumentElement(), graph.getStylesheet());

            // Sets the background to white
            getViewport().setOpaque(false);
            setBackground(Color.WHITE);
        }

        /**
         * Overrides drop behaviour to set the cell style if the target
         * is not a valid drop target and the cells are of the same
         * type (eg. both vertices or both edges). 
         */
        public Object[] importCells(Object[] cells, double dx, double dy,
                Object target, Point location) {
            if (target == null && cells.length == 1 && location != null) {
                target = graph.getCellAt(location.x, location.y);

                if (target instanceof mxICell && cells[0] instanceof mxICell) {
                    mxICell targetCell = (mxICell) target;
                    mxICell dropCell = (mxICell) cells[0];

                    if (targetCell.isVertex() == dropCell.isVertex() || targetCell.isEdge() == dropCell.isEdge()) {
                        mxIGraphModel model = graph.getModel();
                        model.setStyle(target, model.getStyle(cells[0]));
                        graph.setSelectionCell(target);

                        return null;
                    }
                }
            }

            return super.importCells(cells, dx, dy, target, location);
        }
    }

    /**
     * A graph that creates new edges from a given template edge.
     */
    public static class CustomGraph extends mxGraph {

        /**
         * Holds the edge to be used as a template for inserting new edges.
         */
        protected Object edgeTemplate;

        /**
         * Custom graph that defines the alternate edge style to be used when
         * the middle control point of edges is double clicked (flipped).
         */
        public CustomGraph() {
            setAlternateEdgeStyle("edgeStyle=mxEdgeStyle.ElbowConnector;elbow=vertical");
        }

        /**
         * Sets the edge template to be used to inserting edges.
         */
        public void setEdgeTemplate(Object template) {
            edgeTemplate = template;
        }

        /**
         * Prints out some useful information about the cell in the tooltip.
         */
        public String getToolTipForCell(Object cell) {
            String tip = "<html>";
            mxGeometry geo = getModel().getGeometry(cell);
            mxCellState state = getView().getState(cell);

            if (getModel().isEdge(cell)) {
                tip += "points={";

                if (geo != null) {
                    List points = geo.getPoints();

                    if (points != null) {
                        Iterator it = points.iterator();

                        while (it.hasNext()) {
                            mxPoint point = (mxPoint) it.next();
                            tip += "[x=" + numberFormat.format(point.getX()) + ",y=" + numberFormat.format(point.getY()) + "],";
                        }

                        tip = tip.substring(0, tip.length() - 1);
                    }
                }

                tip += "}<br>";
                tip += "absPoints={";

                if (state != null) {

                    for (int i = 0; i < state.getAbsolutePointCount(); i++) {
                        mxPoint point = state.getAbsolutePoint(i);
                        tip += "[x=" + numberFormat.format(point.getX()) + ",y=" + numberFormat.format(point.getY()) + "],";
                    }

                    tip = tip.substring(0, tip.length() - 1);
                }

                tip += "}";
            } else {
                tip += "geo=[";

                if (geo != null) {
                    tip += "x=" + numberFormat.format(geo.getX()) + ",y=" + numberFormat.format(geo.getY()) + ",width=" + numberFormat.format(geo.getWidth()) + ",height=" + numberFormat.format(geo.getHeight());
                }

                tip += "]<br>";
                tip += "state=[";

                if (state != null) {
                    tip += "x=" + numberFormat.format(state.getX()) + ",y=" + numberFormat.format(state.getY()) + ",width=" + numberFormat.format(state.getWidth()) + ",height=" + numberFormat.format(state.getHeight());
                }

                tip += "]";
            }

            mxPoint trans = getView().getTranslate();

            tip += "<br>scale=" + numberFormat.format(getView().getScale()) + ", translate=[x=" + numberFormat.format(trans.getX()) + ",y=" + numberFormat.format(trans.getY()) + "]";
            tip += "</html>";

            return tip;
        }

        /**
         * Overrides the method to use the currently selected edge template for
         * new edges.
         * 
         * @param graph
         * @param parent
         * @param id
         * @param value
         * @param source
         * @param target
         * @param style
         * @return
         */
        public Object insertEdge(Object parent, String id, Object value,
                Object source, Object target, String style) {
            if (edgeTemplate != null) {
                mxCell edge = (mxCell) cloneCells(new Object[]{edgeTemplate})[0];
                edge.setId(id);

                return addEdge(edge, parent, source, target, null);
            }

            return super.insertEdge(parent, id, value, source, target, style);
        }
    }
}
