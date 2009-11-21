#ifndef PROCESSINSTANCE_H_INCLUDED
#define PROCESSINSTANCE_H_INCLUDED

#include <list>

#include "../metadata/processdefinition.h"
#include "defs.h"
#include "token.h"
#include "../metadata/masterentity.h"

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

#endif // PROCESSINSTANCE_H_INCLUDED
