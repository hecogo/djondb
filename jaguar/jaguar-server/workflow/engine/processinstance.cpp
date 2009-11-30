#include "processinstance.h"
#include "tokenfacade.h"

#include "dbjaguar.h"

//**************************************************************************************************
// This file contains simple objects for runtime, this simple objects does not contain complex
// assignation rutines, process or some other stuff. They're just plain objects.
//**************************************************************************************************

using namespace dbjaguar;

ProcessInstance::ProcessInstance()
{
    currentTokens = new list<Token*>();
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

void ProcessInstance::persist() {
    Connection* con = getDefaultDataConnection();
    string sql;
    if (PERSISTENCE_NEW_STATUS(this)) {
        sql = "INSERT INTO PROCESSINSTANCE (id, idprocessdef, status, idmasterent) VALUES (?, ?, ?, ?);";
        Statement* stmt = con->createStatement(sql.c_str());
        stmt->setParameter(0, DBTYPE_INT24, new int(getId()));
        stmt->setParameter(1, DBTYPE_LONG, new long(getProcessDefinition()->getId()));
        stmt->setParameter(2, DBTYPE_INT24, (int*)getStatus());
        int idMasterEnt = 1;
        stmt->setParameter(3, DBTYPE_INT24, new int(idMasterEnt));
        stmt->executeUpdate();
    } else {
        sql = "UPDATE PROCESSINSTANCE SET status = ?, idmasterent = ? WHERE id = ?";
        Statement* stmt = con->createStatement(sql.c_str());
        stmt->setParameter(0, DBTYPE_INT24, (int*)getStatus());
        int idMasterEnt = 1;
        stmt->setParameter(1, DBTYPE_INT24, new int(idMasterEnt));
        stmt->setParameter(2, DBTYPE_INT24, new int(getId()));
        stmt->executeUpdate();
    }
}