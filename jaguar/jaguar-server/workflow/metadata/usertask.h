#include <vector>

class UserTask : public Task {
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

