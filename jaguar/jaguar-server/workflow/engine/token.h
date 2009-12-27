#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include "../metadata/task.h"
#include "defs.h"
#include "processinstance.h"

class Token {
private:
    long id;
    Task* task;
    TokenStatus status;
public:
    long getId();
    void setId(long id);
    Task* getTask();
    void setTask(Task* task);
    TokenStatus getStatus();
    void setStatus(TokenStatus _status);
};


#endif // TOKEN_H_INCLUDED
