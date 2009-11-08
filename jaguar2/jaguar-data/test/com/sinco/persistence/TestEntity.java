/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.persistence;

import java.io.Serializable;
import java.util.ArrayList;

/**
 *
 * @author cross
 */
@Entity
public class TestEntity implements Serializable {

    
    private int id;
    private String name;
    private ArrayList<TestChildEntity> childEntities;
    private transient int mitransient = 0;

    @Id
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<TestChildEntity> getChildEntities() {
        return childEntities;
    }

    public void setChildEntities(ArrayList<TestChildEntity> childEntities) {
        this.childEntities = childEntities;
    }

    public int getMitransient() {
        return mitransient;
    }

    public void setMitransient(int mitransient) {
        this.mitransient = mitransient;
    }
    
}
