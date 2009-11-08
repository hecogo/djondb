package com.mxgraph.swing.examples.editor;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.AbstractAction;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.SwingUtilities;
import javax.swing.TransferHandler;
import javax.swing.UIManager;

import com.mxgraph.swing.mxGraphComponent;
import com.mxgraph.swing.examples.BasicGraphEditor;
import com.mxgraph.swing.examples.editor.EditorActions.AlignCellsAction;
import com.mxgraph.swing.examples.editor.EditorActions.AutosizeAction;
import com.mxgraph.swing.examples.editor.EditorActions.BackgroundAction;
import com.mxgraph.swing.examples.editor.EditorActions.BackgroundImageAction;
import com.mxgraph.swing.examples.editor.EditorActions.ColorAction;
import com.mxgraph.swing.examples.editor.EditorActions.ExitAction;
import com.mxgraph.swing.examples.editor.EditorActions.GridColorAction;
import com.mxgraph.swing.examples.editor.EditorActions.GridStyleAction;
import com.mxgraph.swing.examples.editor.EditorActions.KeyValueAction;
import com.mxgraph.swing.examples.editor.EditorActions.PageBackgroundAction;
import com.mxgraph.swing.examples.editor.EditorActions.PageSetupAction;
import com.mxgraph.swing.examples.editor.EditorActions.PrintAction;
import com.mxgraph.swing.examples.editor.EditorActions.PromptPropertyAction;
import com.mxgraph.swing.examples.editor.EditorActions.PromptValueAction;
import com.mxgraph.swing.examples.editor.EditorActions.RedoAction;
import com.mxgraph.swing.examples.editor.EditorActions.SaveAction;
import com.mxgraph.swing.examples.editor.EditorActions.ScaleAction;
import com.mxgraph.swing.examples.editor.EditorActions.SelectShortestPathAction;
import com.mxgraph.swing.examples.editor.EditorActions.SelectSpanningTreeAction;
import com.mxgraph.swing.examples.editor.EditorActions.SetStyleAction;
import com.mxgraph.swing.examples.editor.EditorActions.StyleAction;
import com.mxgraph.swing.examples.editor.EditorActions.StylesheetAction;
import com.mxgraph.swing.examples.editor.EditorActions.ToggleAction;
import com.mxgraph.swing.examples.editor.EditorActions.ToggleConnectModeAction;
import com.mxgraph.swing.examples.editor.EditorActions.ToggleCreateTargetItem;
import com.mxgraph.swing.examples.editor.EditorActions.ToggleDirtyAction;
import com.mxgraph.swing.examples.editor.EditorActions.ToggleGridItem;
import com.mxgraph.swing.examples.editor.EditorActions.ToggleOutlineItem;
import com.mxgraph.swing.examples.editor.EditorActions.TogglePropertyItem;
import com.mxgraph.swing.examples.editor.EditorActions.ToggleRulersItem;
import com.mxgraph.swing.examples.editor.EditorActions.UndoAction;
import com.mxgraph.swing.examples.editor.EditorActions.WarningAction;
import com.mxgraph.swing.examples.editor.EditorActions.ZoomPolicyAction;
import com.mxgraph.swing.util.mxGraphActions;
import com.mxgraph.util.mxConstants;
import com.mxgraph.util.mxPoint;
import com.mxgraph.util.mxResources;
import com.mxgraph.view.mxGraph;

public class EditorMenuBar extends JMenuBar
{

	public EditorMenuBar(final BasicGraphEditor frame)
	{
		final mxGraphComponent graphComponent = frame.getGraphComponent();
		final mxGraph graph = graphComponent.getGraph();
		JMenu menu = null;
		JMenu submenu = null;

		// Creates the file menu
		menu = add(new JMenu(mxResources.get("file")));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("save"), new SaveAction(false),
				"/com/mxgraph/swing/examples/images/save.gif"));
		menu.add(frame.bind(mxResources.get("saveAs"), new SaveAction(true),
				"/com/mxgraph/swing/examples/images/saveas.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("pageSetup"),
				new PageSetupAction(),
				"/com/mxgraph/swing/examples/images/pagesetup.gif"));
		menu.add(frame.bind(mxResources.get("print"), new PrintAction(),
				"/com/mxgraph/swing/examples/images/print.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("exit"), new ExitAction()));

		// Creates the edit menu
		menu = add(new JMenu(mxResources.get("edit")));

		menu.add(frame.bind(mxResources.get("undo"), new UndoAction(frame),
				"/com/mxgraph/swing/examples/images/undo.gif"));
		menu.add(frame.bind(mxResources.get("redo"), new RedoAction(frame),
				"/com/mxgraph/swing/examples/images/redo.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("cut"), TransferHandler
				.getCutAction(), "/com/mxgraph/swing/examples/images/cut.gif"));
		menu.add(frame
				.bind(mxResources.get("copy"), TransferHandler.getCopyAction(),
						"/com/mxgraph/swing/examples/images/copy.gif"));
		menu.add(frame.bind(mxResources.get("paste"), TransferHandler
				.getPasteAction(),
				"/com/mxgraph/swing/examples/images/paste.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("delete"), mxGraphActions
				.getDeleteAction(),
				"/com/mxgraph/swing/examples/images/delete.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("selectAll"), mxGraphActions
				.getSelectAllAction()));
		menu.add(frame.bind(mxResources.get("selectNone"), mxGraphActions
				.getSelectNoneAction()));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("warning"), new WarningAction()));
		menu.add(frame.bind(mxResources.get("edit"), mxGraphActions
				.getEditAction()));

		// Creates the view menu
		menu = add(new JMenu(mxResources.get("view")));

		JMenuItem item = menu.add(new TogglePropertyItem(graphComponent,
				mxResources.get("pageLayout"), "PageVisible", true,
				new ActionListener()
				{
					/**
					 * 
					 */
					public void actionPerformed(ActionEvent e)
					{
						if (graphComponent.isPageVisible()
								&& graphComponent.isCenterPage())
						{
							graphComponent.zoomAndCenter();
						}
					}
				}));

		item.addActionListener(new ActionListener()
		{
			/*
			 * (non-Javadoc)
			 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			public void actionPerformed(ActionEvent e)
			{
				if (e.getSource() instanceof TogglePropertyItem)
				{
					final mxGraphComponent graphComponent = frame
							.getGraphComponent();
					TogglePropertyItem toggleItem = (TogglePropertyItem) e
							.getSource();

					if (toggleItem.isSelected())
					{
						// Scrolls the view to the center
						SwingUtilities.invokeLater(new Runnable()
						{
							/*
							 * (non-Javadoc)
							 * @see java.lang.Runnable#run()
							 */
							public void run()
							{
								graphComponent.scrollToCenter(true);
								graphComponent.scrollToCenter(false);
							}
						});
					}
					else
					{
						// Resets the translation of the view
						mxPoint tr = graphComponent.getGraph().getView()
								.getTranslate();

						if (tr.getX() != 0 || tr.getY() != 0)
						{
							graphComponent.getGraph().getView().setTranslate(
									new mxPoint());
						}
					}
				}
			}
		});

		menu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("antialias"), "AntiAlias", true));

		menu.addSeparator();

		menu.add(new ToggleGridItem(frame, mxResources.get("grid")));
		menu.add(new ToggleRulersItem(frame, mxResources.get("rulers")));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("zoom")));

		submenu.add(frame.bind("400%", new ScaleAction(4)));
		submenu.add(frame.bind("200%", new ScaleAction(2)));
		submenu.add(frame.bind("150%", new ScaleAction(1.5)));
		submenu.add(frame.bind("100%", new ScaleAction(1)));
		submenu.add(frame.bind("75%", new ScaleAction(0.75)));
		submenu.add(frame.bind("50%", new ScaleAction(0.5)));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("custom"), new ScaleAction(0)));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("zoomIn"), mxGraphActions
				.getZoomInAction()));
		menu.add(frame.bind(mxResources.get("zoomOut"), mxGraphActions
				.getZoomOutAction()));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("page"), new ZoomPolicyAction(
				mxGraphComponent.ZOOM_POLICY_PAGE)));
		menu.add(frame.bind(mxResources.get("width"), new ZoomPolicyAction(
				mxGraphComponent.ZOOM_POLICY_WIDTH)));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("actualSize"), mxGraphActions
				.getZoomActualAction()));

		// Creates the format menu
		menu = add(new JMenu(mxResources.get("format")));

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("alignment")));

		submenu.add(frame.bind(mxResources.get("left"), new KeyValueAction(
				mxConstants.STYLE_ALIGN, mxConstants.ALIGN_LEFT),
				"/com/mxgraph/swing/examples/images/left.gif"));
		submenu.add(frame.bind(mxResources.get("center"), new KeyValueAction(
				mxConstants.STYLE_ALIGN, mxConstants.ALIGN_CENTER),
				"/com/mxgraph/swing/examples/images/center.gif"));
		submenu.add(frame.bind(mxResources.get("right"), new KeyValueAction(
				mxConstants.STYLE_ALIGN, mxConstants.ALIGN_RIGHT),
				"/com/mxgraph/swing/examples/images/right.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("top"), new KeyValueAction(
				mxConstants.STYLE_VERTICAL_ALIGN, mxConstants.ALIGN_TOP),
				"/com/mxgraph/swing/examples/images/top.gif"));
		submenu.add(frame.bind(mxResources.get("middle"), new KeyValueAction(
				mxConstants.STYLE_VERTICAL_ALIGN, mxConstants.ALIGN_MIDDLE),
				"/com/mxgraph/swing/examples/images/middle.gif"));
		submenu.add(frame.bind(mxResources.get("bottom"), new KeyValueAction(
				mxConstants.STYLE_VERTICAL_ALIGN, mxConstants.ALIGN_BOTTOM),
				"/com/mxgraph/swing/examples/images/bottom.gif"));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("colors")));

		submenu.add(frame.bind(mxResources.get("fontcolor"), new ColorAction(
				"Fontcolor", mxConstants.STYLE_FONTCOLOR),
				"/com/mxgraph/swing/examples/images/fontcolor.gif"));
		submenu.add(frame.bind(mxResources.get("linecolor"), new ColorAction(
				"Linecolor", mxConstants.STYLE_STROKECOLOR),
				"/com/mxgraph/swing/examples/images/linecolor.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("fillcolor"), new ColorAction(
				"Fillcolor", mxConstants.STYLE_FILLCOLOR),
				"/com/mxgraph/swing/examples/images/fillcolor.gif"));
		submenu.add(frame.bind(mxResources.get("gradient"), new ColorAction(
				"Gradient", mxConstants.STYLE_GRADIENTCOLOR)));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("labelFill"), new ColorAction(
				"Label Fill", mxConstants.STYLE_LABEL_BACKGROUNDCOLOR)));
		submenu.add(frame.bind(mxResources.get("labelBorder"), new ColorAction(
				"Label Border", mxConstants.STYLE_LABEL_BORDERCOLOR)));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("shadow"), new ToggleAction(
				mxConstants.STYLE_SHADOW)));
		submenu.add(frame.bind(mxResources.get("opacity"),
				new PromptValueAction(mxConstants.STYLE_OPACITY,
						"Opacity (0-100)")));

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("connector")));

		submenu
				.add(frame.bind(mxResources.get("straight"),
						new SetStyleAction("straight"),
						"/com/mxgraph/swing/examples/images/straight.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("horizontal"),
				new SetStyleAction(""),
				"/com/mxgraph/swing/examples/images/connect.gif"));
		submenu
				.add(frame.bind(mxResources.get("vertical"),
						new SetStyleAction("vertical"),
						"/com/mxgraph/swing/examples/images/vertical.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("entityRelation"),
				new SetStyleAction("edgeStyle=mxEdgeStyle.EntityRelation"),
				"/com/mxgraph/swing/examples/images/entity.gif"));
		submenu.add(frame.bind(mxResources.get("arrow"), new SetStyleAction(
				"arrow"), "/com/mxgraph/swing/examples/images/arrow.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("rounded"), new ToggleAction(
				mxConstants.STYLE_ROUNDED)));
		submenu.add(frame.bind(mxResources.get("dashed"), new ToggleAction(
				mxConstants.STYLE_DASHED)));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("linewidth"),
				new PromptValueAction(mxConstants.STYLE_STROKEWIDTH,
						"Linewidth")));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("linestart")));

		submenu.add(frame.bind(mxResources.get("open"), new KeyValueAction(
				mxConstants.STYLE_STARTARROW, mxConstants.ARROW_OPEN),
				"/com/mxgraph/swing/examples/images/open_start.gif"));
		submenu.add(frame.bind(mxResources.get("classic"), new KeyValueAction(
				mxConstants.STYLE_STARTARROW, mxConstants.ARROW_CLASSIC),
				"/com/mxgraph/swing/examples/images/classic_start.gif"));
		submenu.add(frame.bind(mxResources.get("block"), new KeyValueAction(
				mxConstants.STYLE_STARTARROW, mxConstants.ARROW_BLOCK),
				"/com/mxgraph/swing/examples/images/block_start.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("diamond"), new KeyValueAction(
				mxConstants.STYLE_STARTARROW, mxConstants.ARROW_DIAMOND),
				"/com/mxgraph/swing/examples/images/diamond_start.gif"));
		submenu.add(frame.bind(mxResources.get("oval"), new KeyValueAction(
				mxConstants.STYLE_STARTARROW, mxConstants.ARROW_OVAL),
				"/com/mxgraph/swing/examples/images/oval_start.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("none"), new KeyValueAction(
				mxConstants.STYLE_STARTARROW)));
		submenu.add(frame.bind(mxResources.get("size"), new PromptValueAction(
				mxConstants.STYLE_STARTSIZE, "Linestart Size")));

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("lineend")));

		submenu.add(frame.bind(mxResources.get("open"), new KeyValueAction(
				mxConstants.STYLE_ENDARROW, mxConstants.ARROW_OPEN),
				"/com/mxgraph/swing/examples/images/open_end.gif"));
		submenu.add(frame.bind(mxResources.get("classic"), new KeyValueAction(
				mxConstants.STYLE_ENDARROW, mxConstants.ARROW_CLASSIC),
				"/com/mxgraph/swing/examples/images/classic_end.gif"));
		submenu.add(frame.bind(mxResources.get("block"), new KeyValueAction(
				mxConstants.STYLE_ENDARROW, mxConstants.ARROW_BLOCK),
				"/com/mxgraph/swing/examples/images/block_end.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("diamond"), new KeyValueAction(
				mxConstants.STYLE_ENDARROW, mxConstants.ARROW_DIAMOND),
				"/com/mxgraph/swing/examples/images/diamond_end.gif"));
		submenu.add(frame.bind(mxResources.get("oval"), new KeyValueAction(
				mxConstants.STYLE_ENDARROW, mxConstants.ARROW_OVAL),
				"/com/mxgraph/swing/examples/images/oval_end.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("none"), new KeyValueAction(
				mxConstants.STYLE_ENDARROW)));
		submenu.add(frame.bind(mxResources.get("size"), new PromptValueAction(
				mxConstants.STYLE_ENDSIZE, "Linestart Size")));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("spacing")));

		submenu.add(frame.bind(mxResources.get("top"), new PromptValueAction(
				mxConstants.STYLE_SPACING_TOP, "Top Spacing")));
		submenu.add(frame.bind(mxResources.get("right"), new PromptValueAction(
				mxConstants.STYLE_SPACING_RIGHT, "Right Spacing")));
		submenu.add(frame.bind(mxResources.get("bottom"),
				new PromptValueAction(mxConstants.STYLE_SPACING_BOTTOM,
						"Bottom Spacing")));
		submenu.add(frame.bind(mxResources.get("left"), new PromptValueAction(
				mxConstants.STYLE_SPACING_LEFT, "Left Spacing")));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("perimeter"),
				new PromptValueAction(mxConstants.STYLE_PERIMETER_SPACING,
						"Perimeter Spacing")));
		submenu.add(frame.bind(mxResources.get("global"),
				new PromptValueAction(mxConstants.STYLE_SPACING, "Spacing")));

		submenu = (JMenu) menu.add(new JMenu("Direction"));

		submenu.add(frame.bind(mxResources.get("north"), new KeyValueAction(
				mxConstants.STYLE_DIRECTION, mxConstants.DIRECTION_NORTH)));
		submenu.add(frame.bind(mxResources.get("east"), new KeyValueAction(
				mxConstants.STYLE_DIRECTION, mxConstants.DIRECTION_EAST)));
		submenu.add(frame.bind(mxResources.get("south"), new KeyValueAction(
				mxConstants.STYLE_DIRECTION, mxConstants.DIRECTION_SOUTH)));
		submenu.add(frame.bind(mxResources.get("west"), new KeyValueAction(
				mxConstants.STYLE_DIRECTION, mxConstants.DIRECTION_WEST)));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("rotateLabel"), new ToggleAction(
				mxConstants.STYLE_HORIZONTAL, true)));
		menu.add(frame.bind(mxResources.get("rotation"), new PromptValueAction(
				mxConstants.STYLE_ROTATION, "Rotation (0-360)")));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("image"), new PromptValueAction(
				mxConstants.STYLE_IMAGE, "Image")));
		menu.add(frame.bind(mxResources.get("style"), new StyleAction()));

		// Creates the shape menu
		menu = add(new JMenu(mxResources.get("shape")));

		menu.add(frame.bind(mxResources.get("home"), mxGraphActions
				.getHomeAction(),
				"/com/mxgraph/swing/examples/images/house.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("exitGroup"), mxGraphActions
				.getExitGroupAction(),
				"/com/mxgraph/swing/examples/images/up.gif"));
		menu.add(frame.bind(mxResources.get("enterGroup"), mxGraphActions
				.getEnterGroupAction(),
				"/com/mxgraph/swing/examples/images/down.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("group"), mxGraphActions
				.getGroupAction(),
				"/com/mxgraph/swing/examples/images/group.gif"));
		menu.add(frame.bind(mxResources.get("ungroup"), mxGraphActions
				.getUngroupAction(),
				"/com/mxgraph/swing/examples/images/ungroup.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("removeFromGroup"), mxGraphActions
				.getRemoveFromParentAction()));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("collapse"), mxGraphActions
				.getCollapseAction(),
				"/com/mxgraph/swing/examples/images/collapse.gif"));
		menu.add(frame.bind(mxResources.get("expand"), mxGraphActions
				.getExpandAction(),
				"/com/mxgraph/swing/examples/images/expand.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("toBack"), mxGraphActions
				.getToBackAction(),
				"/com/mxgraph/swing/examples/images/toback.gif"));
		menu.add(frame.bind(mxResources.get("toFront"), mxGraphActions
				.getToFrontAction(),
				"/com/mxgraph/swing/examples/images/tofront.gif"));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("align")));

		submenu.add(frame.bind(mxResources.get("left"), new AlignCellsAction(
				mxConstants.ALIGN_LEFT),
				"/com/mxgraph/swing/examples/images/alignleft.gif"));
		submenu.add(frame.bind(mxResources.get("center"), new AlignCellsAction(
				mxConstants.ALIGN_CENTER),
				"/com/mxgraph/swing/examples/images/aligncenter.gif"));
		submenu.add(frame.bind(mxResources.get("right"), new AlignCellsAction(
				mxConstants.ALIGN_RIGHT),
				"/com/mxgraph/swing/examples/images/alignright.gif"));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("top"), new AlignCellsAction(
				mxConstants.ALIGN_TOP),
				"/com/mxgraph/swing/examples/images/aligntop.gif"));
		submenu.add(frame.bind(mxResources.get("middle"), new AlignCellsAction(
				mxConstants.ALIGN_MIDDLE),
				"/com/mxgraph/swing/examples/images/alignmiddle.gif"));
		submenu.add(frame.bind(mxResources.get("bottom"), new AlignCellsAction(
				mxConstants.ALIGN_BOTTOM),
				"/com/mxgraph/swing/examples/images/alignbottom.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("autosize"), new AutosizeAction()));

		// Creates the diagram menu
		menu = add(new JMenu(mxResources.get("diagram")));

		menu.add(new ToggleOutlineItem(frame, mxResources.get("outline")));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("background")));

		submenu.add(frame.bind(mxResources.get("backgroundColor"),
				new BackgroundAction()));
		submenu.add(frame.bind(mxResources.get("backgroundImage"),
				new BackgroundImageAction()));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("pageBackground"),
				new PageBackgroundAction()));

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("grid")));

		submenu.add(frame.bind(mxResources.get("gridSize"),
				new PromptPropertyAction(graph, "Grid Size", "GridSize")));
		submenu.add(frame.bind(mxResources.get("gridColor"),
				new GridColorAction()));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("dashed"), new GridStyleAction(
				mxGraphComponent.GRID_STYLE_DASHED)));
		submenu.add(frame.bind(mxResources.get("dot"), new GridStyleAction(
				mxGraphComponent.GRID_STYLE_DOT)));
		submenu.add(frame.bind(mxResources.get("line"), new GridStyleAction(
				mxGraphComponent.GRID_STYLE_LINE)));
		submenu.add(frame.bind(mxResources.get("cross"), new GridStyleAction(
				mxGraphComponent.GRID_STYLE_CROSS)));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("layout")));

		submenu.add(frame.graphLayout("verticalHierarchical"));
		submenu.add(frame.graphLayout("horizontalHierarchical"));

		submenu.addSeparator();

		submenu.add(frame.graphLayout("verticalPartition"));
		submenu.add(frame.graphLayout("horizontalPartition"));

		submenu.addSeparator();

		submenu.add(frame.graphLayout("verticalStack"));
		submenu.add(frame.graphLayout("horizontalStack"));

		submenu.addSeparator();

		submenu.add(frame.graphLayout("verticalTree"));
		submenu.add(frame.graphLayout("horizontalTree"));

		submenu.addSeparator();

		submenu.add(frame.graphLayout("organicLayout"));

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("selection")));

		submenu.add(frame.bind(mxResources.get("selectPath"),
				new SelectShortestPathAction(false)));
		submenu.add(frame.bind(mxResources.get("selectDirectedPath"),
				new SelectShortestPathAction(true)));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("selectTree"),
				new SelectSpanningTreeAction(false)));
		submenu.add(frame.bind(mxResources.get("selectDirectedTree"),
				new SelectSpanningTreeAction(true)));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("stylesheet")));

		submenu
				.add(frame
						.bind(
								mxResources.get("basicStyle"),
								new StylesheetAction(
										"/com/mxgraph/swing/examples/resources/basic-style.xml")));
		submenu
				.add(frame
						.bind(
								mxResources.get("defaultStyle"),
								new StylesheetAction(
										"/com/mxgraph/swing/examples/resources/default-style.xml")));

		// Creates the options menu
		menu = add(new JMenu(mxResources.get("options")));

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("display")));
		submenu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("buffering"), "TripleBuffered", true));
		submenu.add(frame.bind(mxResources.get("dirty"),
				new ToggleDirtyAction()));

		submenu.addSeparator();

		item = submenu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("centerPage"), "CenterPage", true, new ActionListener()
		{
			/**
			 * 
			 */
			public void actionPerformed(ActionEvent e)
			{
				if (graphComponent.isPageVisible()
						&& graphComponent.isCenterPage())
				{
					graphComponent.zoomAndCenter();
				}
			}
		}));

		submenu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("centerZoom"), "CenterZoom", true));
		submenu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("zoomToSelection"), "KeepSelectionVisibleOnZoom", true));

		submenu.addSeparator();

		submenu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("preferPagesize"), "PreferPageSize", true));
		submenu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("pageBreaks"), "PageBreakVisible", true));

		submenu.addSeparator();

		submenu.add(frame.bind(mxResources.get("tolerance"),
				new PromptPropertyAction(graph, "Tolerance")));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("dragAndDrop")));

		submenu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("dragEnabled"), "DragEnabled"));
		// Note: Using graphComponent as a target disables drop from library
		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("dropEnabled"), "DropEnabled"));

		submenu.addSeparator();

		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("shiftDownwards"), "ShiftDownwards"));
		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("shiftRightwards"), "ShiftRightwards"));

		submenu.addSeparator();

		submenu.add(new TogglePropertyItem(graphComponent.getGraphHandler(),
				mxResources.get("imagePreview"), "ImagePreview"));

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("labels")));

		submenu.add(new TogglePropertyItem(graph,
				mxResources.get("htmlLabels"), "HtmlLabels", true));
		submenu.add(new TogglePropertyItem(graph,
				mxResources.get("showLabels"), "LabelsVisible", true));

		submenu.addSeparator();

		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("moveEdgeLabels"), "EdgeLabelMovable"));
		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("moveVertexLabels"), "VertexLabelMovable"));

		submenu.addSeparator();

		submenu.add(new TogglePropertyItem(graphComponent.getCellEditor(),
				mxResources.get("handleReturn"), "ReturnEnabled"));

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("connections")));

		submenu.add(new TogglePropertyItem(graphComponent, mxResources
				.get("connectable"), "Connectable"));
		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("connectableEdges"), "ConnectableEdges"));

		submenu.addSeparator();

		submenu.add(new ToggleCreateTargetItem(frame, mxResources
				.get("createTarget")));
		submenu.add(frame.bind(mxResources.get("connectMode"),
				new ToggleConnectModeAction()));

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("validation")));

		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("allowDanglingEdges"), "AllowDanglingEdges"));
		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("cloneInvalidEdges"), "CloneInvalidEdges"));

		submenu.addSeparator();

		submenu.add(new TogglePropertyItem(graph,
				mxResources.get("allowLoops"), "AllowLoops"));
		submenu.add(new TogglePropertyItem(graph,
				mxResources.get("multigraph"), "Multigraph"));

		submenu.addSeparator();

		submenu.add(new TogglePropertyItem(graph, mxResources
				.get("disconnectOnMove"), "DisconnectOnMove"));

		// Creates the window menu
		menu = add(new JMenu(mxResources.get("window")));

		UIManager.LookAndFeelInfo[] lafs = UIManager.getInstalledLookAndFeels();

		for (int i = 0; i < lafs.length; i++)
		{
			final String clazz = lafs[i].getClassName();
			menu.add(new AbstractAction(lafs[i].getName())
			{
				public void actionPerformed(ActionEvent e)
				{
					try
					{
						UIManager.setLookAndFeel(clazz);
						SwingUtilities.updateComponentTreeUI(frame);
					}
					catch (Exception e1)
					{
						e1.printStackTrace();
					}
				}
			});
		}

		// Creates the help menu
		menu = add(new JMenu(mxResources.get("help")));

		item = menu.add(new JMenuItem(mxResources.get("aboutGraphEditor")));
		item.addActionListener(new ActionListener()
		{
			/*
			 * (non-Javadoc)
			 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			public void actionPerformed(ActionEvent e)
			{
//				EditorAboutFrame about = new EditorAboutFrame(frame);
//				about.setModal(true);
//
//				// Centers inside the application frame
//				int x = frame.getX() + (frame.getWidth() - about.getWidth())
//						/ 2;
//				int y = frame.getY() + (frame.getHeight() - about.getHeight())
//						/ 2;
//				about.setLocation(x, y);
//
//				// Shows the modal dialog and waits
//				about.setVisible(true);
			}
		});
	}

}
