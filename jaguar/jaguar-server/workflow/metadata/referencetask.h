#ifndef REFERENCETASK_H_INCLUDED
#define REFERENCETASK_H_INCLUDED

class ReferenceTask : Task {
private:
    Task taskRef;
public:
    Task getTaskRef() {
        return taskRef;
    }

    void setTaskRef(Task _taskRef) {
        taskRef = _taskRef;
    }
};



#endif // REFERENCETASK_H_INCLUDED
