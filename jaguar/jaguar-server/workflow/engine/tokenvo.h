#ifndef TOKENVO_H_INCLUDED
#define TOKENVO_H_INCLUDED

#include "taskvo.h"
#include "processinstancevo.h"
#include "defs.h"

class TokenVO {
private:
    long id;
    TaskVO* task;
    ProcessInstanceVO* processInstance;
    TokenStatus* status;

public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    TaskVO* getTask() {
        return task;
    }

    void setTask(TaskVO* _task) {
        task = _task;
    }

    ProcessInstanceVO* getProcessInstanceVO() {
        return processInstance;
    }

    void setProcessInstanceVO(ProcessInstanceVO* _processInstanceVO) {
        processInstance = _processInstanceVO;
    }

    TokenStatus* getTokenStatus() {
        return status;
    }

    void setTokenStatus(TokenStatus* _status) {
        status = _status;
    }
};

#endif // TOKENVO_H_INCLUDED
