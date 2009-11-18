#ifndef PROCESSDEFINITION_H_INCLUDED
#define PROCESSDEFINITION_H_INCLUDED

#include <vector>
#include <string>

#include "defs.h"
#include "property.h"
#include "commonevent.h"
#include "pool.h"
#include "activitycommon.h"

using namespace std;

class ProcessDefinition {
private:
    long id;
    string* definitionName;
    ProcessType* processType;
    vector<Property*>* properties;
    vector<CommonEvent*>* events;
    vector<Pool*>* pools;
    vector<ActivityCommon*>* tasks;
    string* masterEntity;
public:
    ProcessType* getProcessType() {
        return processType;
    }

    void setProcessType(ProcessType* _processType) {
        processType = _processType;
    }

    vector<Property*>* getProperties() {
        return properties;
    }

    void setProperties(vector<Property*>* _properties) {
        properties = _properties;
    }

    vector<Pool*>* getPools() {
        return pools;
    }

    void setPools(vector<Pool*>* _pools) {
        pools = _pools;
    }

    string* getDefinitionName() {
        return definitionName;
    }

    void setDefinitionName(string* _definitionName) {
        definitionName = _definitionName;
    }

    vector<ActivityCommon*>* getTasks() {
        return tasks;
    }

    void setTasks(vector<ActivityCommon*>* _tasks) {
        tasks = _tasks;
    }

    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    vector<CommonEvent*>* getEvents() {
        return events;
    }

    void setEvents(vector<CommonEvent*>* _events) {
        events = _events;
    }

    string* getMasterEntity() {
        return masterEntity;
    }

    void setMasterEntity(string* _masterEntity) {
        masterEntity = _masterEntity;
    }
};



#endif // PROCESSDEFINITION_H_INCLUDED
