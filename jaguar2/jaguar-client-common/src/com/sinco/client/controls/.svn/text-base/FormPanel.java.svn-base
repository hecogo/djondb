/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client.controls;

import java.awt.Component;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.Border;

/**
 *
 * @author cross
 */
public abstract class FormPanel extends JPanel {
    private int idForm;

    public FormPanel() {
        setLayout(new GridBagLayout());
    }
    
    public int getIdForm() {
        return idForm;
    }

    public void setIdForm(int idForm) {
        this.idForm = idForm;
    }
    
    public abstract void addComponents();
    
    public void addComponent(String label, Component control) {
        JLabel labelControl = new JLabel(label);
        labelControl.setLabelFor(control);
        GridBagConstraints c = new GridBagConstraints();
        
        c.fill = GridBagConstraints.HORIZONTAL;
        if (getComponentCount() > 0) {
            c.insets = new Insets(0, 5, 4, 4);
        } else {
            c.insets = new Insets(5, 5, 4, 4);
        }
        add(labelControl, c);

        c.gridwidth = GridBagConstraints.REMAINDER;
        c.weightx = 1.0;
        if (control instanceof Requireable) {
            if (((Requireable)control).isRequired()) {
                // algo
            }
        }
        add(control, c);
    }
    
}
