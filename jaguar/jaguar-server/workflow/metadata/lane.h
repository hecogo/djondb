#ifndef LANE_H_INCLUDED
#define LANE_H_INCLUDED

class Lane {
private:
    long id;
    Pool parentPool;
public:
    long getId() {
        return id;
    }

    void setId(long _id) {
        id = _id;
    }

    Pool* getParentPool() {
        return parentPool;
    }

    void setParentPool(Pool* _parentPool) {
        parentPool = _parentPool;
    }

};

#endif // LANE_H_INCLUDED
