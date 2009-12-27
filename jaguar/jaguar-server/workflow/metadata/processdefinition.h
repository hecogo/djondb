#ifndef PROCESSDEFINITION_H_INCLUDED
#define PROCESSDEFINITION_H_INCLUDED

#include <vector>
#include <string>

#include "defs.h"
#include "property.h"
#include "commonevent.h"
#include "activitycommon.h"
#include <iostream>

using namespace std;

class Pool;

class ProcessDefinition {
private:
    long id;
    string definitionName;
    ProcessType processType;
    vector<Property*> properties;
    vector<CommonEvent*> events;
    vector<Pool*> pools;
    vector<ActivityCommon*> activities;
    string masterEntity;
public:
    virtual ~ProcessDefinition() {
        for (vector<ActivityCommon*>::iterator iter = activities.begin(); iter != activities.end(); iter++) {
            ActivityCommon* activity = *iter;
            delete(activity);
        }
        activities.clear();
        for (vector<CommonEvent*>::iterator iter = events.begin(); iter != events.end(); iter++) {
            CommonEvent* evt = *iter;
            delete(evt);
        }
        events.clear();
    }
    
    ProcessType getProcessType() {
        return processType;
    }

    void setProcessType(ProcessType _processType) {
        processType = _processType;
    }

    vector<Property*> getProperties() {
        return properties;
    }

    void setProperties(vector<Property*> _properties) {
        properties = _properties;
    }

    vector<Pool*> getPools() {
        return pools;
    }

    void setPools(vector<Pool*> _pools) {
        pools = _pools;
    }

    string getDefinitionName() {
        return definitionName;
    }

    void setDefinitionName(string _definitionName) {
        definitionName = _definitionName;
    }

    vector<ActivityCommon*> getActivities() {
        return activities;
    }

    void setActivities(vector<ActivityCommon*> _activities) {
        activities = _activities;
    }

    ActivityCommon* getActivity(long idActivity) {
        for (vector<ActivityCommon*>::iterator iter = activities.begin(); iter != activities.end(); iter++) {
            if (((ActivityCommon*)(*iter))->getId() == idActivity) {
                return *iter;
            }
        }
        return NULL;
    }

    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    vector<CommonEvent*> getEvents() {
        return events;
    }

    void setEvents(vector<CommonEvent*> _events) {
        events = _events;
    }

    CommonEvent* getEvent(long idEvent) {
        for (vector<CommonEvent*>::iterator iter = events.begin(); iter != events.end(); iter++) {
            if (((CommonEvent*)(*iter))->getId() == idEvent) {
                return *iter;
            }
        }
        return NULL;
    }
    
    string getMasterEntity() {
        return masterEntity;
    }

    void setMasterEntity(string _masterEntity) {
        masterEntity = _masterEntity;
    }
};

#endif // PROCESSDEFINITION_H_INCLUDED
