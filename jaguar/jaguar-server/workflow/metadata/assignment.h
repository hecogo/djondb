#ifndef ASSIGNMENT_H_INCLUDED
#define ASSIGNMENT_H_INCLUDED

class Assignment {
private:
    long id;
    Property* assignmentTo;
    Expression* assignmentFrom;
    AssignTime* assignTime;
    Expression* expression;
    CommonEvent* event;

public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    Property* getAssignmentTo() {
        return assignmentTo;
    }

    void setAssignmentTo(Property* _assignmentTo) {
        assignmentTo = _assignmentTo;
    }

    Expression* getAssignmentFrom() {
        return assignmentFrom;
    }

    void setAssignmentFrom(Expression* _assignmentFrom) {
        assignmentFrom = _assignmentFrom;
    }

    AssignTime* getAssignTime() {
        return assignTime;
    }

    void setAssignTime(AssignTime* _assignTime) {
        assignTime = _assignTime;
    }

    Expression* getExpression() {
        return expression;
    }

    void setExpression(Expression* _expression) {
        expression = _expression;
    }

    CommonEvent* getEvent() {
        return event;
    }

    void setEvent(CommonEvent* _event) {
        event = _event;
    }
};

#endif // ASSIGNMENT_H_INCLUDED
