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
public abstract class MasterEntity extends JaguarDataEntity implements Serializable {
    private static final long serialVersionUID = 1L;
    protected Long id;

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
        if (!(object instanceof MasterEntity)) {
            return false;
        }
        MasterEntity other = (MasterEntity) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "com.sinco.bpm.data.entities.MasterEntity[id=" + id + "]";
    }

}
