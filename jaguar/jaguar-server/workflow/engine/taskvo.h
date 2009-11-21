#ifndef TASKVO_H_INCLUDED
#define TASKVO_H_INCLUDED

class TaskVO {
private:
    long id;
    string* taskName;
    TaskType taskType;
    int form;

public:
    string* getTaskName() {
        return taskName;
    }

    void setTaskName(string* _taskName) {
        taskName = _taskName;
    }

    TaskType getTaskType() {
        return taskType;
    }

    void setTaskType(TaskType _taskType) {
        taskType = _taskType;
    }

    void setId(long _id) {
        id = _id;
    }

    long getId() {
        return id;
    }

    int getForm() {
        return form;
    }

    void setForm(int _form) {
        form = _form;
    }
};

#endif // TASKVO_H_INCLUDED
