#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include "../metadata/task.h"
#include "defs.h"
#include "processinstance.h"

class Token {
private:
    long id;
    Task* task;
    ProcessInstance* processInstance;
    TokenStatus status;
public:
    long getId();
    void setId(long id);
    Task* getTask();
    void setTask(Task* task);
    ProcessInstance* getProcessInstance();
    void setProcessInstance(ProcessInstance* processInstance);
    TokenStatus getStatus();
    void setStatus(TokenStatus _status);
};


#endif // TOKEN_H_INCLUDED
