#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <vector>
#include <string>

#include "defs.h"
#include "connectorsourceable.h"
#include "connectortargetable.h"
#include "activitycommon.h"

using namespace std;


class Task : public ConnectorSourceable, public ConnectorTargetable, public ActivityCommon {
private:
    vector<CommonConector*>* sequenceFlows;
    TaskType* taskType;
    string* taskName;
public:
    TaskType* getTaskType() {
        return taskType;
    }

    void setTaskType(TaskType* _taskType) {
        taskType = _taskType;
    }

    vector<CommonConector*>* getSequenceFlows() {
        return sequenceFlows;
    }

    void setSequenceFlows(vector<CommonConector*>* _sequenceFlows) {
        sequenceFlows = _sequenceFlows;
    }

    string* getTaskName() {
        return taskName;
    }

    void setTaskName(string* _taskName) {
        taskName = _taskName;
    }

};



#endif // TASK_H_INCLUDED
