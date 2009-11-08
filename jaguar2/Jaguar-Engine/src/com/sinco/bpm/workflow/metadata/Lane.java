package com.sinco.bpm.workflow.metadata;

public class Lane implements java.io.Serializable {
    
    private long id;
    
    private Pool parentPool;
    
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Pool getParentPool() {
        return parentPool;
    }

    public void setParentPool(Pool parentPool) {
        this.parentPool = parentPool;
    }
}