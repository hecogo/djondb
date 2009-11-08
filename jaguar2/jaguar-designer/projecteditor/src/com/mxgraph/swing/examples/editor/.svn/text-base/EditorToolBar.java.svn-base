package com.mxgraph.swing.examples.editor;

import java.awt.Dimension;
import java.awt.GraphicsEnvironment;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JToolBar;
import javax.swing.TransferHandler;

import com.mxgraph.swing.mxGraphComponent;
import com.mxgraph.swing.examples.BasicGraphEditor;
import com.mxgraph.swing.examples.editor.EditorActions.ColorAction;
import com.mxgraph.swing.examples.editor.EditorActions.FontStyleAction;
import com.mxgraph.swing.examples.editor.EditorActions.KeyValueAction;
import com.mxgraph.swing.examples.editor.EditorActions.PrintAction;
import com.mxgraph.swing.examples.editor.EditorActions.RedoAction;
import com.mxgraph.swing.examples.editor.EditorActions.SaveAction;
import com.mxgraph.swing.examples.editor.EditorActions.UndoAction;
import com.mxgraph.swing.util.mxGraphActions;
import com.mxgraph.util.mxConstants;
import com.mxgraph.util.mxResources;
import com.mxgraph.util.mxEventSource.mxEventListener;
import com.mxgraph.view.mxGraph;
import com.mxgraph.view.mxGraphView;

public class EditorToolBar extends JToolBar
{

	/**
	 * 
	 * @param frame
	 * @param orientation
	 */
	private boolean ignoreZoomChange = false;

	/**
	 * 
	 */
	public EditorToolBar(final BasicGraphEditor frame, int orientation)
	{
		super(orientation);
		setBorder(BorderFactory.createCompoundBorder(BorderFactory
				.createEmptyBorder(3, 3, 3, 3), getBorder()));
		setFloatable(false);

		add(frame.bind("Save", new SaveAction(false),
				"/com/mxgraph/swing/examples/images/save.gif"));

		addSeparator();

		add(frame.bind("Print", new PrintAction(),
				"/com/mxgraph/swing/examples/images/print.gif"));

		addSeparator();

		add(frame.bind("Cut", TransferHandler.getCutAction(),
				"/com/mxgraph/swing/examples/images/cut.gif"));
		add(frame.bind("Copy", TransferHandler.getCopyAction(),
				"/com/mxgraph/swing/examples/images/copy.gif"));
		add(frame.bind("Paste", TransferHandler.getPasteAction(),
				"/com/mxgraph/swing/examples/images/paste.gif"));

		addSeparator();

		add(frame.bind("Delete", mxGraphActions.getDeleteAction(),
				"/com/mxgraph/swing/examples/images/delete.gif"));

		addSeparator();

		add(frame.bind("Undo", new UndoAction(frame),
				"/com/mxgraph/swing/examples/images/undo.gif"));
		add(frame.bind("Redo", new RedoAction(frame),
				"/com/mxgraph/swing/examples/images/redo.gif"));

		addSeparator();

		// Gets the list of available fonts from the local graphics environment
		// and adds some frequently used fonts at the beginning of the list
		GraphicsEnvironment env = GraphicsEnvironment
				.getLocalGraphicsEnvironment();
		List fonts = new ArrayList();
		fonts.addAll(Arrays.asList(new String[] { "Helvetica", "Verdana",
				"Times New Roman", "Garamond", "Courier New", "-" }));
		fonts.addAll(Arrays.asList(env.getAvailableFontFamilyNames()));

		final JComboBox fontCombo = new JComboBox(fonts.toArray());
		fontCombo.setEditable(true);
		fontCombo.setMinimumSize(new Dimension(120, 0));
		fontCombo.setPreferredSize(new Dimension(120, 0));
		fontCombo.setMaximumSize(new Dimension(120, 100));
		add(fontCombo);

		fontCombo.addActionListener(new ActionListener()
		{
			/**
			 * 
			 */
			public void actionPerformed(ActionEvent e)
			{
				String font = fontCombo.getSelectedItem().toString();

				if (font != null && !font.equals("-"))
				{
					mxGraph graph = frame.getGraphComponent().getGraph();
					graph.setCellStyles(mxConstants.STYLE_FONTFAMILY, font);
				}
			}
		});

		final JComboBox sizeCombo = new JComboBox(new Object[] { "6pt", "8pt",
				"9pt", "10pt", "12pt", "14pt", "18pt", "24pt", "30pt", "36pt",
				"48pt", "60pt" });
		sizeCombo.setEditable(true);
		sizeCombo.setMinimumSize(new Dimension(65, 0));
		sizeCombo.setPreferredSize(new Dimension(65, 0));
		sizeCombo.setMaximumSize(new Dimension(65, 100));
		add(sizeCombo);

		sizeCombo.addActionListener(new ActionListener()
		{
			/**
			 * 
			 */
			public void actionPerformed(ActionEvent e)
			{
				mxGraph graph = frame.getGraphComponent().getGraph();
				graph.setCellStyles(mxConstants.STYLE_FONTSIZE, sizeCombo
						.getSelectedItem().toString().replace("pt", ""));
			}
		});

		addSeparator();

		add(frame.bind("Bold", new FontStyleAction(true),
				"/com/mxgraph/swing/examples/images/bold.gif"));
		add(frame.bind("Italic", new FontStyleAction(false),
				"/com/mxgraph/swing/examples/images/italic.gif"));

		addSeparator();

		add(frame.bind("Left", new KeyValueAction(mxConstants.STYLE_ALIGN,
				mxConstants.ALIGN_LEFT),
				"/com/mxgraph/swing/examples/images/left.gif"));
		add(frame.bind("Center", new KeyValueAction(mxConstants.STYLE_ALIGN,
				mxConstants.ALIGN_CENTER),
				"/com/mxgraph/swing/examples/images/center.gif"));
		add(frame.bind("Right", new KeyValueAction(mxConstants.STYLE_ALIGN,
				mxConstants.ALIGN_RIGHT),
				"/com/mxgraph/swing/examples/images/right.gif"));

		addSeparator();

		add(frame.bind("Font", new ColorAction("Font",
				mxConstants.STYLE_FONTCOLOR),
				"/com/mxgraph/swing/examples/images/fontcolor.gif"));
		add(frame.bind("Stroke", new ColorAction("Stroke",
				mxConstants.STYLE_STROKECOLOR),
				"/com/mxgraph/swing/examples/images/linecolor.gif"));
		add(frame.bind("Fill", new ColorAction("Fill",
				mxConstants.STYLE_FILLCOLOR),
				"/com/mxgraph/swing/examples/images/fillcolor.gif"));

		addSeparator();

		final mxGraphView view = frame.getGraphComponent().getGraph().getView();
		final JComboBox zoomCombo = new JComboBox(new Object[] { "400%",
				"200%", "150%", "100%", "75%", "50%", mxResources.get("page"),
				mxResources.get("width"), mxResources.get("actualSize") });
		zoomCombo.setEditable(true);
		zoomCombo.setMinimumSize(new Dimension(75, 0));
		zoomCombo.setPreferredSize(new Dimension(75, 0));
		zoomCombo.setMaximumSize(new Dimension(75, 100));
		zoomCombo.setMaximumRowCount(9);
		add(zoomCombo);

		// Sets the zoom in the zoom combo the current value
		mxEventListener scaleTracker = new mxEventListener()
		{
			/**
			 * 
			 */
			public void invoke(Object sender, Object[] args)
			{
				ignoreZoomChange = true;

				try
				{
					zoomCombo.setSelectedItem((int) Math.round(100 * view
							.getScale())
							+ "%");
				}
				finally
				{
					ignoreZoomChange = false;
				}
			}
		};

		// Installs the scale tracker to update the value in the combo box
		// if the zoom is changed from outside the combo box
		view.getGraph().getView().addListener(mxGraphView.EVENT_SCALE,
				scaleTracker);
		view.getGraph().getView().addListener(
				mxGraphView.EVENT_SCALE_AND_TRANSLATE, scaleTracker);
		
		// Invokes once to sync with the actual zoom value
		scaleTracker.invoke(null, null);

		zoomCombo.addActionListener(new ActionListener()
		{
			/**
			 * 
			 */
			public void actionPerformed(ActionEvent e)
			{
				mxGraphComponent graphComponent = frame.getGraphComponent();

				// Zoomcombo is changed when the scale is changed in the diagram
				// but the change is ignored here
				if (!ignoreZoomChange)
				{
					String zoom = zoomCombo.getSelectedItem().toString();

					if (zoom.equals(mxResources.get("page")))
					{
						graphComponent.setPageVisible(true);
						graphComponent
								.setZoomPolicy(mxGraphComponent.ZOOM_POLICY_PAGE);
					}
					else if (zoom.equals(mxResources.get("width")))
					{
						graphComponent.setPageVisible(true);
						graphComponent
								.setZoomPolicy(mxGraphComponent.ZOOM_POLICY_WIDTH);
					}
					else if (zoom.equals(mxResources.get("actualSize")))
					{
						graphComponent.zoomActual();
					}
					else
					{
						try
						{
							zoom = zoom.replace("%", "");
							graphComponent.zoomTo(
									Double.parseDouble(zoom) / 100,
									graphComponent.isCenterZoom());
						}
						catch (Exception ex)
						{
							JOptionPane.showMessageDialog(frame, ex
									.getMessage());
						}
					}
				}
			}
		});
	}
}
