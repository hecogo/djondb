#include "token.h"
#include "../metadata/task.h"

long Token::getId() {
    return id;
};

void Token::setId(long _id) {
    id = _id;
};

Task* Token::getTask() {
    return task;
};

void Token::setTask(Task* _task) {
    task = _task;
};

ProcessInstance* Token::getProcessInstance() {
    return processInstance;
};


void Token::setProcessInstance(ProcessInstance* _processInstance) {
    processInstance = _processInstance;
};

TokenStatus Token::getStatus() {
    return status;
};

void Token::setStatus(TokenStatus _status) {
    status = _status;
};

