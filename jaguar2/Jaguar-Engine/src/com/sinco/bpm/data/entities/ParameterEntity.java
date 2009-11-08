/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.data.entities;

import java.io.Serializable;

/**
 *
 * @author cross
 */
public abstract class ParameterEntity extends JaguarDataEntity implements Serializable {
    private static final long serialVersionUID = 1L;
    protected Long id;
    
    protected String description;

    public void setId(Long id) {
        this.id = id;
    }

    public Long getId() {
        return id;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof ParameterEntity)) {
            return false;
        }
        ParameterEntity other = (ParameterEntity) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "com.sinco.bpm.data.entities.ParameterEntity[id=" + id + "]";
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

}
