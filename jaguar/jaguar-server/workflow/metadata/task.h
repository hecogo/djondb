#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>

#include "defs.h"
#include "connectorsourceable.h"
#include "connectortargetable.h"
#include "activitycommon.h"
#include "commonconnector.h"
#include "util.h"

using namespace std;

class Task : public ConnectorSourceable, public ConnectorTargetable, public ActivityCommon {
private:
    vector<CommonConector*> sequenceFlows;
    TaskType taskType;
    string taskName;
public:

    virtual ~Task() {
        Logger* log = getLogger(NULL);
        if (log->isDebug()) log->debug("~Task()");
        for (vector<CommonConector*>::iterator iter = sequenceFlows.begin(); iter != sequenceFlows.end(); iter++) {
            CommonConector* connector = *iter;
            delete(connector);
        }
        sequenceFlows.clear();
        delete(log);
    }

    TaskType getTaskType() {
        return taskType;
    }

    void setTaskType(TaskType _taskType) {
        taskType = _taskType;
    }

    vector<CommonConector*> getSequenceFlows() {
        return sequenceFlows;
    }

    void addSequenceFlow(CommonConector* connector) {
        sequenceFlows.push_back(connector);
    }
    
    string getTaskName() {
        return taskName;
    }

    void setTaskName(string _taskName) {
        taskName = _taskName;
    }

};



#endif // TASK_H_INCLUDED
