#include "metadata.h"
#include <typeinfo>
#include <fstream>
#include <dirent.h>
#include "metadata/entitynotfoundexception.h"
#include "metadata/servicetask.h"
#include "metadata/activitycommon.h"
#include "metadata/task.h"

using namespace std;
using namespace dbjaguar;
using namespace cache;

vector<ActivityCommon*>* loadTasks(Connection* con, ProcessDefinition* def) {
    Logger* log = getLogger(NULL);
    try {
        if (log->isDebug()) log->debug("Loading tasks definition for: " + *def->getDefinitionName());

        vector<ActivityCommon*>* res = new vector<ActivityCommon*>();

        long idDef = def->getId();
        string sql = "SELECT t.id, t.taskname, "
                "t.tasktype, a.activitytype, a.startquantity, a.looptype FROM task t inner join activities a on t.idactivity = a.id "
                "where a.idprocessdef = " + toString(idDef);
        ResultSet* rs = con->executeQuery(sql.c_str());

        while ((*rs)++) {
            long *id = (long*) rs->get("id");
            string* taskName = (string*) rs->get("taskname");
            TaskType taskType = static_cast<TaskType> (*(short int*) rs->get("tasktype"));
            ActivityType actType = static_cast<ActivityType> (*(short int*) rs->get("activitytype"));
            int *startQuantity = (int*) rs->get("startquantity");
            LoopType loopType = static_cast<LoopType> (*(short int*) rs->get("looptype"));

            Task* task;
            switch (taskType) {
                case SERVICE_TASKTYPE:
                    task = new ServiceTask();
                    break;
            }
            task->setId(*id);
            task->setActivityType(&actType);
            task->setLoopType(&loopType);
            task->setProcessDefinition(def);
            task->setStartQuantity(*startQuantity);
            task->setTaskName(taskName);
            task->setTaskType(&taskType);
            res->push_back(task);
        }
        return res;
    } catch (DBException e) {
        log->error(e.what());
    }
}

void loadProcessDefinitions(Connection* con) {
    Logger* log = getLogger(NULL);

    if (log->isInfo()) log->info("Loading process definitions");

    CacheGroup* cache = getGlobalCache("METADATA");
    ResultSet* rs = con->executeQuery("SELECT id, defname, processType, masterent FROM processdef");

    map<long, ProcessDefinition*>* mapDefinitions = new map<long, ProcessDefinition*>();
    while ((*rs)++) {
        long* id = (long*) rs->get(0);
        string* defname = (string*) rs->get(1);
        ProcessType processType = static_cast<ProcessType> (*(short int*) rs->get(2));
        string* masterent = (string*) rs->get(3);
        ProcessDefinition* def = new ProcessDefinition();
        def->setProcessType(&processType);
        //def->setProperties(vector<Property*>* _properties);
        //def->setPools(vector<Pool*>* _pools);
        def->setDefinitionName(defname);
        def->setId(*id);
        //def->setEvents(vector<CommonEvent*>* _events);
        def->setMasterEntity(masterent);

        if (log->isDebug()) log->debug("Adding process definition: " + *defname);
        mapDefinitions->insert(pair<long, ProcessDefinition*>(*id, def));
    }

    rs->close();

    if (log->isDebug()) log->debug("Loading tasks definitions");
    for (map<long, ProcessDefinition*>::iterator iter = mapDefinitions->begin(); iter != mapDefinitions->end(); iter++) {
        ProcessDefinition* def = iter->second;
        def->setTasks(loadTasks(con, def));
    }
    
    cache->add("PROCESSDEFINITIONS", mapDefinitions);
}

ProcessDefinition* getProcessDefinition(long id) throw (WorkflowException) {
    CacheGroup* group = getGlobalCache("METADATA");
    map<long, ProcessDefinition*>* definitions = (map<long, ProcessDefinition*>*)group->get("PROCESSDEFINITIONS");
    if (!definitions) {
        throw new WorkflowException("The process definition does not exist");
    }
    ProcessDefinition* def = definitions->find(id)->second;
    if (!def) {
        throw new WorkflowException("The process definition does not exist");
    }
    return def;
}

void deserialize(string fileName, void** readed) {
    ifstream file;
    file.open(fileName.c_str(), ios::binary);
    file.read((char*) readed, sizeof (*readed));
    file.close();
}

void serialize(string filename, void* file) {
    ofstream ofile;
    ofile.open(filename.c_str(), ios::binary);
    ofile.write((char*) file, sizeof (file));
    ofile.close();
}

const char* EntityNotFoundException::what() const throw () {
    return message->c_str();
}


