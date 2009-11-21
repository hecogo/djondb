#include "tokenfacade.h"

#include "../metadata/task.h"
#include "defs.h"
#include "../metadata/defs.h"

void executePostUser(Token* token)
{
    TokenStatus s = POSTUSER;
    token->setStatus(s);
}

Token* getNextStatus(list<Token*>* tokens)
{
    for (list<Token*>::iterator it = tokens->begin(); it != tokens->end(); it++) {
        Token* token = *it;
        if (token->getStatus() == NONE)
        {
            return token;
        }
        if (token->getStatus() == POSTUSER)
        {
            return token;
        }
    }
    return NULL;
}

void executeEnd(Token* token)
{
    token->setStatus(ENDED);
}

void executeStart(Token* token)
{
    token->setStatus(STARTED);
//        Task task = token.getTask();
}

list<Token*>* getNextTokens(ProcessInstance* processInstance, Token* token)
{
    vector<CommonConector*>* sequenceFlows = token->getTask()->getSequenceFlows();
    list<Token*>* result = new list<Token*>();
    for (vector<CommonConector*>::iterator it = sequenceFlows->begin(); it != sequenceFlows->end(); it++) {
        CommonConector* connector = *it;
        if (connector->getTargetType() == TASK)
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
            }
            newToken->setProcessInstance(processInstance);
            newToken->setStatus(NONE);
            newToken->setTask(task);
            processInstance->addCurrentToken(newToken);
            result->push_back(newToken);
        }
    }
    return result;
}

list<Token*>* TokenFacade::processToken(ProcessInstance* processInstance, Token* token)
{
    list<Token*>* res = new list<Token*>();
    if (token->getStatus() == USER)
    {
        executePostUser(token);
    }
    res->push_back(token);
    while ((token = getNextStatus(res)) != NULL)
    {
        res->remove(token);
        if (token->getStatus() == NONE)
        {
            executeStart(token);
        }
        if ((token->getStatus() == STARTED)
                && (*token->getTask()->getTaskType() == MANUAL_TASKTYPE))
        {
            token->setStatus(USER);
            res->push_back(token);
        }
        if ((token->getStatus() == STARTED)
                || (token->getStatus() == POSTUSER))
        {
            executeEnd(token);
            res->remove(token);
            // Replaces the exit tokens with the new ones
            list<Token*>* tokens = getNextTokens(processInstance, token);
            for (list<Token*>::iterator it = tokens->begin(); it != tokens->end(); it++) {
                res->push_back(*it);
            }
        }
    }
    return res;
}

Token* TokenFacade::findBy(TokenVO token)
{
    return NULL;
}
