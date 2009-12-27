#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

class Expression {
private:
    long id;
    string expression;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string getExpression() {
        return expression;
    }

    void setExpression(string _expression) {
        expression = _expression;
    }
};



#endif // EXPRESSION_H_INCLUDED
