package com.sinco.bpm.workflow.metadata;

import com.sinco.persistence.Id;

@com.sinco.persistence.Entity
public class Expression implements java.io.Serializable {

    private long id;
    
    private String expression;

    @Id
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getExpression() {
        return expression;
    }

    public void setExpression(String expression) {
        this.expression = expression;
    }
    
}