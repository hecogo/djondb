#ifndef POOL_H_INCLUDED
#define POOL_H_INCLUDED

#include <vector>

class Lane;
class Participant;
class ProcessDefinition;

class Pool {
private:
    long id;
    string* poolName;
    vector<Lane*>* lanes;
    Participant* participant;
    ProcessDefinition* processDefinition;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string* getPoolName() {
        return poolName;
    }

    void setPoolName(string* _poolName) {
        poolName = _poolName;
    }

    vector<Lane*>* getLanes() {
        return lanes;
    }

    void setLanes(vector<Lane*>* _lanes) {
        lanes = _lanes;
    }

    Participant* getParticipant() {
        return participant;
    }

    void setParticipant(Participant* _participant) {
        participant = _participant;
    }

    ProcessDefinition* getProcessDefinition() {
        return processDefinition;
    }

    void setProcessDefinition(ProcessDefinition* _processDefinition) {
        processDefinition = _processDefinition;
    }
};


#endif // POOL_H_INCLUDED
