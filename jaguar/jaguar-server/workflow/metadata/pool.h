#ifndef POOL_H_INCLUDED
#define POOL_H_INCLUDED

#include <vector>
#include <string>
#include "participant.h"

using namespace std;

class Lane;
class ProcessDefinition;

class Pool {
private:
    long id;
    string poolName;
    vector<Lane*> lanes;
    Participant participant;

public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    string getPoolName() {
        return poolName;
    }

    void setPoolName(string _poolName) {
        poolName = _poolName;
    }

    vector<Lane*> getLanes() {
        return lanes;
    }

    void setLanes(vector<Lane*> _lanes) {
        lanes = _lanes;
    }

    Participant getParticipant() {
        return participant;
    }

    void setParticipant(Participant _participant) {
        participant = _participant;
    }
};


#endif // POOL_H_INCLUDED
