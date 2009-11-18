#ifndef MANUALTASK_H_INCLUDED
#define MANUALTASK_H_INCLUDED

class ManualTask : public Task {
private:
    vector<void*>* performers;
public:
    vector<void*>* getPerformers() {
        return performers;
    }

    void setPerformers(vector<void*>* _performers) {
        performers = _performers;
    }
};



#endif // MANUALTASK_H_INCLUDED
