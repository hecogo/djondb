#include "wfruntime.h"
//**************************************************************************************************
// This file contains simple objects for runtime, this simple objects does not contain complex
// assignation rutines, process or some other stuff. They're just plain objects.
//**************************************************************************************************
ProcessInstance::ProcessInstance()
{
}

void ProcessInstance::addCurrentToken(Token* token)
{
    currentTokens->push_back(token);
}

void ProcessInstance::addCurrentToken(list<Token*>* token)
{
    currentTokens->assign(token->begin(), token->end());
}

int ProcessInstance::getId()
{
    return id;
}

void ProcessInstance::setId(int _id)
{
    id = _id;
}

ProcessDefinition* ProcessInstance::getProcessDefinition()
{
    return processDefinition;
}

void ProcessInstance::setProcessDefinition(ProcessDefinition* _processDefinition)
{
    processDefinition = _processDefinition;
}

InstanceStatus* ProcessInstance::getStatus()
{
    return status;
}

void ProcessInstance::setStatus(InstanceStatus* _status)
{
    status = _status;
}

list<void*>* ProcessInstance::getAssignments()
{
    return assignments;
}

void ProcessInstance::setAssignments(list<void*>* _assignments)
{
    assignments = _assignments;
}

list<void*>* ProcessInstance::getPropertyValues()
{
    return propertyValues;
}

void ProcessInstance::setPropertyValues(list<void*>* _propertyValues)
{
    propertyValues = _propertyValues;
}

list<Token*>* ProcessInstance::getCurrentTokens()
{
    return currentTokens;
}

MasterEntity* ProcessInstance::getMasterEntity()
{
    return masterEntity;
}

void ProcessInstance::setMasterEntity(MasterEntity* _masterEntity)
{
    masterEntity = _masterEntity;
}

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

