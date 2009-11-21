#ifndef PROCESSINSTANCEVO_H_INCLUDED
#define PROCESSINSTANCEVO_H_INCLUDED

class ProcessInstanceVO {
private:
    int id;
    string* processName;

public:
    int getId() {
        return id;
    }

    void setId(int _id) {
        id = _id;
    }

    string* getProcessName() {
        return processName;
    }

    void setProcessName(string* _processName) {
        processName = _processName;
    }

};


#endif // PROCESSINSTANCEVO_H_INCLUDED
