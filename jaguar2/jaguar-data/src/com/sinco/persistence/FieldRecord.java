/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.persistence;

import java.io.Serializable;

/**
 *
 * @author cross
 */
class FieldRecord implements Serializable {

    private String fieldName;
    private Object value;

    public FieldRecord(String fieldName, Object value) {
        this.fieldName = fieldName;
        this.value = value;
    }

    public String getFieldName() {
        return fieldName;
    }

    public Object getValue() {
        return value;
    }
}