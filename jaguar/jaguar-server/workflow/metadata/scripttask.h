#ifndef SCRIPTTASK_H_INCLUDED
#define SCRIPTTASK_H_INCLUDED

class ScriptTask : Task {
private:
    string script;
public:
    string getScript() {
        return script;
    }

    void setScript(string _script) {
        script = _script;
    }
};


#endif // SCRIPTTASK_H_INCLUDED
