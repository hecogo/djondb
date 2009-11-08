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
class Token;

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

