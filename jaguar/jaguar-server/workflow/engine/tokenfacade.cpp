#include "tokenfacade.h"

#include "../metadata/task.h"
#include "defs.h"
#include "../metadata/defs.h"
#include "dbjaguar.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

using namespace dbjaguar;

void executePostUser(Token* token)
{
    TokenStatus s = TOKENSTATUS_POSTUSER;
    token->setStatus(s);
}

Token* getNextStatus(list<Token*>* tokens)
{
    for (list<Token*>::iterator it = tokens->begin(); it != tokens->end(); it++) {
        Token* token = *it;
        if (token->getStatus() == TOKENSTATUS_NONE)
        {
            return token;
        }
        if (token->getStatus() == TOKENSTATUS_POSTUSER)
        {
            return token;
        }
    }
    return NULL;
}

void executeEnd(Token* token)
{
    token->setStatus(TOKENSTATUS_ENDED);
}

void executeStart(Token* token)
{
    token->setStatus(TOKENSTATUS_STARTED);
//        Task task = token.getTask();
}

list<Token*>* getNextTokens(ProcessInstance* processInstance, Token* token)
{
    vector<CommonConector*> sequenceFlows = token->getTask()->getSequenceFlows();
    list<Token*>* result = new list<Token*>();
    for (vector<CommonConector*>::iterator it = sequenceFlows.begin(); it != sequenceFlows.end(); it++) {
        CommonConector* connector = *it;
        if (connector->getTargetType() == TASK_CTTYPE)
        {
            Task* task = connector->getTaskTarget();
            Token* newToken;
            if (result->size() == 0)
            {
                newToken = token;
            }
            else
            {
                newToken = new Token();
                newToken->setId(getNextKey("token"));
            }
            newToken->setStatus(TOKENSTATUS_NONE);
            newToken->setTask(task);
            processInstance->addCurrentToken(newToken);
            result->push_back(newToken);
        }
    }
    return result;
}

list<Token*>* processToken(ProcessInstance* processInstance, Token* token)
{
    list<Token*>* res = new list<Token*>();
    if (token->getStatus() == TOKENSTATUS_USER)
    {
        executePostUser(token);
    }
    res->push_back(token);
    while ((token = getNextStatus(res)) != NULL)
    {
        res->remove(token);
        if (token->getStatus() == TOKENSTATUS_NONE)
        {
            executeStart(token);
        }
        if ((token->getStatus() == TOKENSTATUS_STARTED)
                && (token->getTask()->getTaskType() == MANUAL_TASKTYPE))
        {
            token->setStatus(TOKENSTATUS_USER);
            res->push_back(token);
        }
        if ((token->getStatus() == TOKENSTATUS_STARTED)
                || (token->getStatus() == TOKENSTATUS_POSTUSER))
        {
            executeEnd(token);
            res->remove(token);
            // Replaces the exit tokens with the new ones
            list<Token*>* tokens = getNextTokens(processInstance, token);
            for (list<Token*>::iterator it = tokens->begin(); it != tokens->end(); it++) {
                res->push_back(*it);
            }
            delete(token);
        }
    }
    return res;
}

Token* findTokenBy(TokenVO token)
{
    return NULL;
}

Task* getTask(ProcessDefinition* def, long idTask) {
    vector<ActivityCommon*>* activities = def->getActivities();
    for (vector<ActivityCommon*>::iterator iter = activities->begin(); iter != activities->end(); iter++) {
        ActivityCommon* activity = *iter;
        if (activity->getId() == idTask) {
            return (Task*)activity;
        }
    }
    return NULL;
}

void closeCurrentTokens(ProcessInstance* processInstance) {
    //TODO Implementar un metodo para hacer un solo update si el token esta cambiando
    // y no es removido
    Connection* con = getDefaultDataConnection();
    // Ended all the current tokens
    string sqlUpdate("UPDATE tokens SET status = ? WHERE idprocessinst = ?");
    Statement* stmt = con->createStatement(sqlUpdate.c_str());
    int idProcess = processInstance->getId();
    int status = TOKENSTATUS_ENDED;
    stmt->setParameter(0, DBTYPE_LONG, &status);
    stmt->setParameter(1, DBTYPE_LONG, &idProcess);
    stmt->executeUpdate();
    stmt->close();
    delete(stmt);

    con->close();
    delete(con);
}

void persistCurrentTokens(ProcessInstance* processInstance) {
    closeCurrentTokens(processInstance);
    
    Connection* con = getDefaultDataConnection();
    list<Token*>* tokens = processInstance->getCurrentTokens();
    if (!tokens) {
        return;
    }

    for (list<Token*>::iterator iter = tokens->begin(); iter != tokens->end(); iter++) {
        Token* token = *iter;
        string sqlUpdate("UPDATE tokens SET idtask = ?, status = ? WHERE id = ?");
        Statement* stmt = con->createStatement(sqlUpdate.c_str());
        int idTask = token->getTask()->getId();
        stmt->setParameter(0, DBTYPE_LONG, &idTask);
        int status = token->getStatus();
        stmt->setParameter(1, DBTYPE_LONG, &status);
        int id = token->getId();
        stmt->setParameter(2, DBTYPE_LONG, &id);
        int res = stmt->executeUpdate();
        stmt->close();
        delete(stmt);
        if (res == 0) {
            string sqlInsert("INSERT INTO tokens (id, idtask, idprocessinst, status) VALUES (?, ?, ?, ?)");
            Statement* stmtInsert = con->createStatement(sqlInsert.c_str());
            stmtInsert->setParameter(0, DBTYPE_LONG, &id);
            stmtInsert->setParameter(1, DBTYPE_LONG, &idTask);
            int idProcessInst = processInstance->getId();
            stmtInsert->setParameter(2, DBTYPE_LONG, &idProcessInst);
            stmtInsert->setParameter(3, DBTYPE_LONG, &status);
            stmtInsert->executeUpdate();
            stmtInsert->close();
            delete(stmtInsert);
        }
    }
    con->close();
    delete(con);
}

void loadCurrentTokens(ProcessInstance* processInstance) {
    Connection* con = getDefaultDataConnection();
    char* sql = (char*)malloc(1024);
    memset(sql, 0, 1024);
    format(sql, "SELECT id, idtask, idprocessinst, status FROM tokens WHERE idprocessinst = %d", processInstance->getId());
    ResultSet* rs = con->executeQuery(sql);
    ProcessDefinition* def = processInstance->getProcessDefinition();
    while (rs->next()) {
        Token* token = new Token();
        token->setId(*(static_cast<int*>(rs->get("id"))));
        TokenStatus status = (TokenStatus)*(static_cast<long*>(rs->get("status")));
        token->setStatus(status);
        token->setTask(getTask(def, *(static_cast<long *>(rs->get("idtask")))));
        processInstance->addCurrentToken(token);
    }
    free(sql);
    rs->close();
    delete(rs);
    con->close();
    delete(con);
}
