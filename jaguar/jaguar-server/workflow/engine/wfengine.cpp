#include "wfruntime.h"

using namespace cache;

class TokenFacade {
public:
    list<Token*>* processToken(ProcessInstance* processInstance, Token* token) {
        Task* currentTask = token->getTask();
        return NULL;
    }

    Token* findBy(TokenVO token) {
        return NULL;
    }
};

vector<StartEvent*>* getStartEvents(ProcessDefinition* def)
{
    vector<CommonEvent*>* commonEvents = def->getEvents();
    vector<StartEvent*>* startEvents = new vector<StartEvent*>();
    for (vector<CommonEvent*>::iterator com = commonEvents->begin(); com != commonEvents->end(); com++)
    {
        if (typeid(*com) == typeid(StartEvent))
        {
            startEvents->push_back((StartEvent*)*com);
        }
    }
    // If the process definition does not contain start events the workflow
    // will create a virtual StartEvent with the tasks with no incoming
    // flow
    if (startEvents->size() == 0)
    {
        throw "Not implemented yet";
    }
    return startEvents;
}


ProcessInstance* processEvent(ProcessInstance* processInstance, StartEvent* evt)
{
    // Every new process generates a new tokens
    vector<CommonConector*>* sequenceFlows = evt->getSequenceFlows();
    TokenFacade* tokenFacade = new TokenFacade();
    for (vector<CommonConector*>::iterator connector = sequenceFlows->begin();
            connector != sequenceFlows->end(); connector++)
    {
        ConnectorTargetable* target = (*connector)->getTaskTarget();
        if (target)
        {
            Token* token = new Token();
            Task* task = (Task*) target;
            token->setTask(task);
            token->setProcessInstance(processInstance);
            token->setStatus(NONE);
            list<Token*>* newTokens = tokenFacade->processToken(processInstance, token);
            if (newTokens)
            {
                processInstance->addCurrentToken(newTokens);
            }
        }
    }

    return processInstance;
}

list<Token*>* processToken(ProcessInstance* instance, TokenVO* tokenVO)
{
    try
    {
        TokenFacade* tokenFacade = new TokenFacade();
        Token* token = tokenFacade->findBy(*tokenVO);
        return tokenFacade->processToken(instance, token);
    }
    catch (EntityNotFoundException ex)
    {
        stringstream smessage;
        smessage << "Wrong token definition. The token id: " << tokenVO->getId() << " was not found." << endl;
        throw smessage.str();
    }
};

ProcessInstance* persist(ProcessInstance* processInstance) {
    // TODO To be implemented
    return processInstance;
}

// creates a new instance from the process definition
ProcessInstance* createProcessInstance(long definition)
{
    ProcessInstance* processInstance = new ProcessInstance();
    ProcessDefinition* def = getProcessDefinition(definition);
    processInstance->setProcessDefinition(def);
    //MasterEntity master = getMasterEntity(def);
    //processInstance.setMasterEntity(master);
    vector<StartEvent*>* startEvents = getStartEvents(def);
    for (vector<StartEvent*>::iterator evt = startEvents->begin(); evt != startEvents->end(); evt++)
    {
        processInstance = processEvent(processInstance, *evt);
    }
    processInstance = persist(processInstance);

    return processInstance;
};

