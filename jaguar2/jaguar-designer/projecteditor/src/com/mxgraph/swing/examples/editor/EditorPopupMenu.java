package com.mxgraph.swing.examples.editor;

import javax.swing.JMenu;
import javax.swing.JPopupMenu;
import javax.swing.TransferHandler;

import com.mxgraph.swing.examples.BasicGraphEditor;
import com.mxgraph.swing.examples.editor.EditorActions.AlignCellsAction;
import com.mxgraph.swing.examples.editor.EditorActions.AutosizeAction;
import com.mxgraph.swing.examples.editor.EditorActions.ColorAction;
import com.mxgraph.swing.examples.editor.EditorActions.KeyValueAction;
import com.mxgraph.swing.examples.editor.EditorActions.PromptValueAction;
import com.mxgraph.swing.examples.editor.EditorActions.SetStyleAction;
import com.mxgraph.swing.examples.editor.EditorActions.StyleAction;
import com.mxgraph.swing.examples.editor.EditorActions.ToggleAction;
import com.mxgraph.swing.examples.editor.EditorActions.UndoAction;
import com.mxgraph.swing.util.mxGraphActions;
import com.mxgraph.util.mxConstants;
import com.mxgraph.util.mxResources;

public class EditorPopupMenu extends JPopupMenu
{

	public EditorPopupMenu(BasicGraphEditor frame)
	{
		boolean selected = !frame.getGraphComponent().getGraph()
				.isSelectionEmpty();

		add(frame.bind(mxResources.get("undo"), new UndoAction(frame),
				"/com/mxgraph/swing/examples/images/undo.gif"));

		addSeparator();

		add(
				frame
						.bind(mxResources.get("cut"), TransferHandler
								.getCutAction(),
								"/com/mxgraph/swing/examples/images/cut.gif"))
				.setEnabled(selected);
		add(
				frame.bind(mxResources.get("copy"), TransferHandler
						.getCopyAction(),
						"/com/mxgraph/swing/examples/images/copy.gif")).setEnabled(
				selected);
		add(frame.bind(mxResources.get("paste"), TransferHandler
				.getPasteAction(), "/com/mxgraph/swing/examples/images/paste.gif"));

		addSeparator();

		add(
				frame.bind(mxResources.get("delete"), mxGraphActions
						.getDeleteAction(),
						"/com/mxgraph/swing/examples/images/delete.gif")).setEnabled(
				selected);

		addSeparator();

		// Creates the format menu
		JMenu menu = (JMenu) add(new JMenu(mxResources.get("format")));

		JMenu submenu = (JMenu) menu
				.add(new JMenu(mxResources.get("alignment")));

		submenu.add(
				frame.bind(mxResources.get("left"), new KeyValueAction(
						mxConstants.STYLE_ALIGN, mxConstants.ALIGN_LEFT),
						"/com/mxgraph/swing/examples/images/left.gif")).setEnabled(
				selected);
		submenu.add(
				frame.bind(mxResources.get("center"), new KeyValueAction(
						mxConstants.STYLE_ALIGN, mxConstants.ALIGN_CENTER),
						"/com/mxgraph/swing/examples/images/center.gif")).setEnabled(
				selected);
		submenu.add(
				frame.bind(mxResources.get("right"), new KeyValueAction(
						mxConstants.STYLE_ALIGN, mxConstants.ALIGN_RIGHT),
						"/com/mxgraph/swing/examples/images/right.gif")).setEnabled(
				selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("top"),
						new KeyValueAction(mxConstants.STYLE_VERTICAL_ALIGN,
								mxConstants.ALIGN_TOP),
						"/com/mxgraph/swing/examples/images/top.gif")).setEnabled(
				selected);
		submenu.add(
				frame.bind(mxResources.get("middle"), new KeyValueAction(
						mxConstants.STYLE_VERTICAL_ALIGN,
						mxConstants.ALIGN_MIDDLE),
						"/com/mxgraph/swing/examples/images/middle.gif")).setEnabled(
				selected);
		submenu.add(
				frame.bind(mxResources.get("bottom"), new KeyValueAction(
						mxConstants.STYLE_VERTICAL_ALIGN,
						mxConstants.ALIGN_BOTTOM),
						"/com/mxgraph/swing/examples/images/bottom.gif")).setEnabled(
				selected);

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("colors")));

		submenu.add(
				frame.bind(mxResources.get("fontcolor"), new ColorAction(
						"Fontcolor", mxConstants.STYLE_FONTCOLOR),
						"/com/mxgraph/swing/examples/images/fontcolor.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("linecolor"), new ColorAction(
						"Linecolor", mxConstants.STYLE_STROKECOLOR),
						"/com/mxgraph/swing/examples/images/linecolor.gif"))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("fillcolor"), new ColorAction(
						"Fillcolor", mxConstants.STYLE_FILLCOLOR),
						"/com/mxgraph/swing/examples/images/fillcolor.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("gradient"), new ColorAction(
						"Gradient", mxConstants.STYLE_GRADIENTCOLOR)))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu
				.add(
						frame
								.bind(
										mxResources.get("labelFill"),
										new ColorAction(
												"Label Fill",
												mxConstants.STYLE_LABEL_BACKGROUNDCOLOR)))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("labelBorder"), new ColorAction(
						"Label Border", mxConstants.STYLE_LABEL_BORDERCOLOR)))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("shadow"), new ToggleAction(
						mxConstants.STYLE_SHADOW))).setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("opacity"), new PromptValueAction(
						mxConstants.STYLE_OPACITY, "Opacity (0-100)")))
				.setEnabled(selected);

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("connector")));

		submenu.add(
				frame.bind(mxResources.get("straight"), new SetStyleAction(
						"straight"),
						"/com/mxgraph/swing/examples/images/straight.gif"))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("horizontal"),
						new SetStyleAction(""),
						"/com/mxgraph/swing/examples/images/connect.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("vertical"), new SetStyleAction(
						"vertical"),
						"/com/mxgraph/swing/examples/images/vertical.gif"))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("entityRelation"),
						new SetStyleAction(
								"edgeStyle=mxEdgeStyle.EntityRelation"),
						"/com/mxgraph/swing/examples/images/entity.gif")).setEnabled(
				selected);
		submenu.add(
				frame.bind(mxResources.get("arrow"),
						new SetStyleAction("arrow"),
						"/com/mxgraph/swing/examples/images/arrow.gif")).setEnabled(
				selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("rounded"), new ToggleAction(
						mxConstants.STYLE_ROUNDED))).setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("dashed"), new ToggleAction(
						mxConstants.STYLE_DASHED))).setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("linewidth"), new PromptValueAction(
						mxConstants.STYLE_STROKEWIDTH, "Linewidth")))
				.setEnabled(selected);

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("linestart")));

		submenu.add(
				frame.bind(mxResources.get("open"), new KeyValueAction(
						mxConstants.STYLE_STARTARROW, mxConstants.ARROW_OPEN),
						"/com/mxgraph/swing/examples/images/open_start.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("classic"),
						new KeyValueAction(mxConstants.STYLE_STARTARROW,
								mxConstants.ARROW_CLASSIC),
						"/com/mxgraph/swing/examples/images/classic_start.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("block"), new KeyValueAction(
						mxConstants.STYLE_STARTARROW, mxConstants.ARROW_BLOCK),
						"/com/mxgraph/swing/examples/images/block_start.gif"))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("diamond"),
						new KeyValueAction(mxConstants.STYLE_STARTARROW,
								mxConstants.ARROW_DIAMOND),
						"/com/mxgraph/swing/examples/images/diamond_start.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("oval"), new KeyValueAction(
						mxConstants.STYLE_STARTARROW, mxConstants.ARROW_OVAL),
						"/com/mxgraph/swing/examples/images/oval_start.gif"))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("none"), new KeyValueAction(
						mxConstants.STYLE_STARTARROW))).setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("size"), new PromptValueAction(
						mxConstants.STYLE_STARTSIZE, "Linestart Size")))
				.setEnabled(selected);

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("lineend")));

		submenu.add(
				frame.bind(mxResources.get("open"), new KeyValueAction(
						mxConstants.STYLE_ENDARROW, mxConstants.ARROW_OPEN),
						"/com/mxgraph/swing/examples/images/open_end.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("classic"), new KeyValueAction(
						mxConstants.STYLE_ENDARROW, mxConstants.ARROW_CLASSIC),
						"/com/mxgraph/swing/examples/images/classic_end.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("block"), new KeyValueAction(
						mxConstants.STYLE_ENDARROW, mxConstants.ARROW_BLOCK),
						"/com/mxgraph/swing/examples/images/block_end.gif"))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("diamond"), new KeyValueAction(
						mxConstants.STYLE_ENDARROW, mxConstants.ARROW_DIAMOND),
						"/com/mxgraph/swing/examples/images/diamond_end.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("oval"), new KeyValueAction(
						mxConstants.STYLE_ENDARROW, mxConstants.ARROW_OVAL),
						"/com/mxgraph/swing/examples/images/oval_end.gif"))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("none"), new KeyValueAction(
						mxConstants.STYLE_ENDARROW))).setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("size"), new PromptValueAction(
						mxConstants.STYLE_ENDSIZE, "Linestart Size")))
				.setEnabled(selected);

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("spacing")));

		submenu.add(
				frame.bind(mxResources.get("top"), new PromptValueAction(
						mxConstants.STYLE_SPACING_TOP, "Top Spacing")))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("right"), new PromptValueAction(
						mxConstants.STYLE_SPACING_RIGHT, "Right Spacing")))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("bottom"), new PromptValueAction(
						mxConstants.STYLE_SPACING_BOTTOM, "Bottom Spacing")))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("left"), new PromptValueAction(
						mxConstants.STYLE_SPACING_LEFT, "Left Spacing")))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("perimeter"), new PromptValueAction(
						mxConstants.STYLE_PERIMETER_SPACING,
						"Perimeter Spacing"))).setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("global"), new PromptValueAction(
						mxConstants.STYLE_SPACING, "Spacing"))).setEnabled(
				selected);

		submenu = (JMenu) menu.add(new JMenu("Direction"));

		submenu.add(
				frame.bind(mxResources.get("north"), new KeyValueAction(
						mxConstants.STYLE_DIRECTION,
						mxConstants.DIRECTION_NORTH))).setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("east"),
						new KeyValueAction(mxConstants.STYLE_DIRECTION,
								mxConstants.DIRECTION_EAST))).setEnabled(
				selected);
		submenu.add(
				frame.bind(mxResources.get("south"), new KeyValueAction(
						mxConstants.STYLE_DIRECTION,
						mxConstants.DIRECTION_SOUTH))).setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("west"),
						new KeyValueAction(mxConstants.STYLE_DIRECTION,
								mxConstants.DIRECTION_WEST))).setEnabled(
				selected);

		menu.addSeparator();

		menu.add(
				frame.bind(mxResources.get("rotateLabel"), new ToggleAction(
						mxConstants.STYLE_HORIZONTAL, true))).setEnabled(
				selected);
		menu.add(
				frame.bind(mxResources.get("rotation"), new PromptValueAction(
						mxConstants.STYLE_ROTATION, "Rotation (0-360)")))
				.setEnabled(selected);

		menu.addSeparator();

		menu.add(
				frame.bind(mxResources.get("image"), new PromptValueAction(
						mxConstants.STYLE_IMAGE, "Image")))
				.setEnabled(selected);
		menu.add(frame.bind(mxResources.get("style"), new StyleAction()))
				.setEnabled(selected);

		// Creates the shape menu
		menu = (JMenu) add(new JMenu(mxResources.get("shape")));

		menu.add(frame.bind(mxResources.get("home"), mxGraphActions
				.getHomeAction(), "/com/mxgraph/swing/examples/images/house.gif"));

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("exitGroup"), mxGraphActions
				.getExitGroupAction(), "/com/mxgraph/swing/examples/images/up.gif"));
		menu.add(
				frame.bind(mxResources.get("enterGroup"), mxGraphActions
						.getEnterGroupAction(),
						"/com/mxgraph/swing/examples/images/down.gif")).setEnabled(
				selected);

		menu.addSeparator();

		menu.add(
				frame.bind(mxResources.get("group"), mxGraphActions
						.getGroupAction(),
						"/com/mxgraph/swing/examples/images/group.gif")).setEnabled(
				selected);
		menu.add(
				frame.bind(mxResources.get("ungroup"), mxGraphActions
						.getUngroupAction(),
						"/com/mxgraph/swing/examples/images/ungroup.gif"))
				.setEnabled(selected);

		menu.addSeparator();

		menu.add(
				frame.bind(mxResources.get("removeFromGroup"), mxGraphActions
						.getRemoveFromParentAction())).setEnabled(selected);

		menu.addSeparator();

		menu.add(
				frame.bind(mxResources.get("collapse"), mxGraphActions
						.getCollapseAction(),
						"/com/mxgraph/swing/examples/images/collapse.gif"))
				.setEnabled(selected);
		menu.add(
				frame.bind(mxResources.get("expand"), mxGraphActions
						.getExpandAction(),
						"/com/mxgraph/swing/examples/images/expand.gif")).setEnabled(
				selected);

		menu.addSeparator();

		menu.add(
				frame.bind(mxResources.get("toBack"), mxGraphActions
						.getToBackAction(),
						"/com/mxgraph/swing/examples/images/toback.gif")).setEnabled(
				selected);
		menu.add(
				frame.bind(mxResources.get("toFront"), mxGraphActions
						.getToFrontAction(),
						"/com/mxgraph/swing/examples/images/tofront.gif"))
				.setEnabled(selected);

		menu.addSeparator();

		submenu = (JMenu) menu.add(new JMenu(mxResources.get("align")));

		submenu.add(
				frame.bind(mxResources.get("left"), new AlignCellsAction(
						mxConstants.ALIGN_LEFT),
						"/com/mxgraph/swing/examples/images/alignleft.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("center"), new AlignCellsAction(
						mxConstants.ALIGN_CENTER),
						"/com/mxgraph/swing/examples/images/aligncenter.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("right"), new AlignCellsAction(
						mxConstants.ALIGN_RIGHT),
						"/com/mxgraph/swing/examples/images/alignright.gif"))
				.setEnabled(selected);

		submenu.addSeparator();

		submenu.add(
				frame.bind(mxResources.get("top"), new AlignCellsAction(
						mxConstants.ALIGN_TOP),
						"/com/mxgraph/swing/examples/images/aligntop.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("middle"), new AlignCellsAction(
						mxConstants.ALIGN_MIDDLE),
						"/com/mxgraph/swing/examples/images/alignmiddle.gif"))
				.setEnabled(selected);
		submenu.add(
				frame.bind(mxResources.get("bottom"), new AlignCellsAction(
						mxConstants.ALIGN_BOTTOM),
						"/com/mxgraph/swing/examples/images/alignbottom.gif"))
				.setEnabled(selected);

		menu.addSeparator();

		menu.add(frame.bind(mxResources.get("autosize"), new AutosizeAction()))
				.setEnabled(selected);

		addSeparator();

		add(frame.bind(mxResources.get("edit"), mxGraphActions.getEditAction()))
				.setEnabled(selected);

		addSeparator();

		add(frame.bind(mxResources.get("selectVertices"), mxGraphActions
				.getSelectVerticesAction()));
		add(frame.bind(mxResources.get("selectEdges"), mxGraphActions
				.getSelectEdgesAction()));

		addSeparator();

		add(frame.bind(mxResources.get("selectAll"), mxGraphActions
				.getSelectAllAction()));
	}

}
