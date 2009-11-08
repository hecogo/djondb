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
@Entity
public class TestChildEntity implements Serializable {

    private int id;
    private String childName;
    private TestEntity parentEntity;

    @Id
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getChildName() {
        return childName;
    }

    public void setChildName(String childName) {
        this.childName = childName;
    }

    public TestEntity getParentEntity() {
        return parentEntity;
    }

    public void setParentEntity(TestEntity parentEntity) {
        this.parentEntity = parentEntity;
    }
    
}
