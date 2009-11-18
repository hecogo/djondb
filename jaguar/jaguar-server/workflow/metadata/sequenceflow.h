#ifndef SEQUENCEFLOW_H_INCLUDED
#define SEQUENCEFLOW_H_INCLUDED

class SequenceFlow : CommonConector {
private:
    ConditionType* conditionType;
    Expression* conditionExpression;
    int quantity;
public:
    ConditionType* getConditionType() {
        return conditionType;
    }

    void setConditionType(ConditionType* _conditionType) {
        conditionType = _conditionType;
    }

    Expression* getConditionExpression() {
        return conditionExpression;
    }

    void setConditionExpression(Expression* _conditionExpression) {
        conditionExpression = _conditionExpression;
    }

    int getQuantity() {
        return quantity;
    }

    void setQuantity(int _quantity) {
        quantity = _quantity;
    }
};

#endif // SEQUENCEFLOW_H_INCLUDED
