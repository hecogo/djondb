/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client.controls;

import java.awt.BorderLayout;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 *
 * @author cross
 */
public class TextField extends JPanel implements Control, Requireable {
    private JTextField text;
    
    private boolean editable;
    private String xPath;
    private boolean required;
    
    public TextField() {
        text = new JTextField();
        setLayout(new BorderLayout());
        add(text, BorderLayout.CENTER);
    }
    
    public boolean hasValue() {
        return !text.getText().isEmpty();
    }

    public Object getValue() {
        return text.getText();
    }

    public void setValue(Object value) {
        text.setText(value.toString());
    }

    public boolean isEditable() {
        return editable;
    }

    public void setEditable(boolean editable) {
        this.editable = editable;
    }

    public String getXPath() {
        return xPath;
    }

    public void setXPath(String xPath) {
        this.xPath = xPath;
    }

    public boolean isRequired() {
        return required;
    }

    public void setRequired(boolean required) {
        this.required = required;
    }

}
