#include "../metadata/metadata.h"
#include <list>

enum InstanceStatus
{
    RUNNING,
    CLOSED,
    CANCELLED
};

enum TokenStatus {
    NONE,
    STARTED,
    USER,
    POSTUSER,
    ENDED
};

class MasterEntity;
class ProcessInstance;
class ProcessInstanceVO;
class Token;
class TokenVO;
class TaskVO;

class ProcessInstance
{
private:
    int id;
    ProcessDefinition* processDefinition;
    InstanceStatus* status;
    list<void*>* assignments;
    list<void*>* propertyValues;
    list<Token*>* currentTokens;
    MasterEntity* masterEntity;
public:
    ProcessInstance();
    void addCurrentToken(Token* token);
    void addCurrentToken(list<Token*>* token);
    int getId();
    void setId(int id);
    ProcessDefinition* getProcessDefinition();
    void setProcessDefinition(ProcessDefinition* processDefinition);
    InstanceStatus* getStatus();
    void setStatus(InstanceStatus* status);
    list<void*>* getAssignments();
    void setAssignments(list<void*>* assignments);
    list<void*>* getPropertyValues();
    void setPropertyValues(list<void*>* propertyValues);
    list<Token*>* getCurrentTokens();
    MasterEntity* getMasterEntity();
    void setMasterEntity(MasterEntity* masterEntity);
};

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
    void setStatus(TokenStatus status);
};

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

class TaskVO {
private:
    long id;
    string* taskName;
    TaskType taskType;
    int form;

public:
    string* getTaskName() {
        return taskName;
    }

    void setTaskName(string* _taskName) {
        taskName = _taskName;
    }

    TaskType getTaskType() {
        return taskType;
    }

    void setTaskType(TaskType _taskType) {
        taskType = _taskType;
    }

    void setId(long _id) {
        id = _id;
    }

    long getId() {
        return id;
    }

    int getForm() {
        return form;
    }

    void setForm(int _form) {
        form = _form;
    }
};


class ProcessInstanceVO {
private:
    int id;
    string* processName;

public:
    int getId() {
        return id;
    }

    void setId(int _id) {
        id = _id;
    }

    string* getProcessName() {
        return processName;
    }

    void setProcessName(string* _processName) {
        processName = _processName;
    }

};
