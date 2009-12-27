#ifndef ACTIVITYCOMMON_H_INCLUDED
#define ACTIVITYCOMMON_H_INCLUDED

class ProcessDefinition;

class ActivityCommon {
private:
    long id;
    ActivityType activityType;
    ActivityStatus status;
    int startQuantity; // Number of tokens required to start the activity
    LoopType loopType;


public:
    ActivityCommon() {
        startQuantity = 1;
    }

    virtual ~ActivityCommon() {
    }
    
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    ActivityType getActivityType() {
        return activityType;
    }

    void setActivityType(ActivityType _activityType) {
        activityType = _activityType;
    }

    ActivityStatus getStatus() {
        return status;
    }

    void setStatus(ActivityStatus _status) {
        status = _status;
    }

    int getStartQuantity() {
        return startQuantity;
    }

    void setStartQuantity(int _startQuantity) {
        startQuantity = _startQuantity;
    }

    LoopType getLoopType() {
        return loopType;
    }

    void setLoopType(LoopType _loopType) {
        loopType = _loopType;
    }
};

#endif // ACTIVITYCOMMON_H_INCLUDED
