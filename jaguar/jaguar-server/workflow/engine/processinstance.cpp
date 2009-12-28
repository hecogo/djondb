#include <iostream>
#include "processinstance.h"
#include "tokenfacade.h"
#include "util.h"
#include "dbjaguar.h"
#include "../metadata.h"
#include "tokenfacade.h"
#include <stdlib.h>
#include <string.h>
//**************************************************************************************************
// This file contains simple objects for runtime, this simple objects does not contain complex
// assignation rutines, process or some other stuff. They're just plain objects.
//**************************************************************************************************

using namespace dbjaguar;

ProcessInstance::ProcessInstance()
{
    currentTokens = new list<Token*>();
    SETPERSISTENCE_NEW_STATUS(this);
}

ProcessInstance::~ProcessInstance() {
    delete(currentTokens);
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

InstanceStatus ProcessInstance::getStatus()
{
    return status;
}

void ProcessInstance::setStatus(InstanceStatus _status)
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
    string* sql;
    if (PERSISTENCE_NEW_STATUS(this)) {
        sql = new string("INSERT INTO processinstance (id, idprocessdef, status, idmasterent) VALUES (?, ?, ?, ?);");
        int id = getNextKey("processinstance");
        setId(id);
	cout << *sql << endl;
        Statement* stmt = con->createStatement(sql->c_str());
        stmt->setParameter(0, DBTYPE_LONG, &id);
        int idProcDef = getProcessDefinition()->getId();
        stmt->setParameter(1, DBTYPE_LONG, &idProcDef);
	int status = getStatus();
        stmt->setParameter(2, DBTYPE_LONG, &status);
        int idMasterEnt = 1;
        stmt->setParameter(3, DBTYPE_LONG, &idMasterEnt);
        stmt->executeUpdate();
        stmt->close();
        delete(stmt);
    } else {
        sql = new string("UPDATE processinstance SET status = ?, idmasterent = ? WHERE id = ?");
        Statement* stmt = con->createStatement(sql->c_str());
	int status = getStatus();
        stmt->setParameter(0, DBTYPE_LONG, &status);
        int idMasterEnt = 1;
        stmt->setParameter(1, DBTYPE_LONG, &idMasterEnt);
	int id = getId();
        stmt->setParameter(2, DBTYPE_LONG, &id);
        stmt->executeUpdate();
        stmt->close();
        delete(stmt);
    }
    delete(sql);
    con->close();
    delete(con);
    persistCurrentTokens(this);

}

//********************************************************************************
// Global Functions
//********************************************************************************
ProcessInstance* loadInstance(int id) {
    Connection* con = getDefaultDataConnection();
    char* sql = (char*)malloc(1024);
    memset(sql, 0, 1024);
    format(sql, "SELECT id, idprocessdef, status, idmasterent from processinstance where id = %d", id);
    ResultSet* rs = con->executeQuery(sql);
    ProcessInstance* processInstance = NULL;
    if (rs->next()) {
        processInstance = new ProcessInstance();
        processInstance->setId(id);
        processInstance->setMasterEntity(NULL); // TODO

        int* idProcessDef = static_cast<int *>(rs->get("idprocessdef"));
        processInstance->setProcessDefinition(getProcessDefinition(*idProcessDef));
        int* status = static_cast<int*>(rs->get("status"));
        processInstance->setStatus((InstanceStatus)*status);
        SETPERSISTENCE_SAVED_STATUS(processInstance);
        
        loadCurrentTokens(processInstance);
    }
    free(sql);
    rs->close();
    delete(rs);
    con->close();
    delete(con);
    return processInstance;
}