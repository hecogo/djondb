package com.sinco.bpm.workflow.metadata;


@com.sinco.persistence.Entity
public class SequenceFlow extends CommonConector implements java.io.Serializable {
    
    private ConditionType conditionType;
    
    private Expression conditionExpression;
    
    private int quantity = 1;

    public ConditionType getConditionType() {
        return conditionType;
    }

    public void setConditionType(ConditionType conditionType) {
        this.conditionType = conditionType;
    }

    public Expression getConditionExpression() {
        return conditionExpression;
    }

    public void setConditionExpression(Expression conditionExpression) {
        this.conditionExpression = conditionExpression;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
    
}