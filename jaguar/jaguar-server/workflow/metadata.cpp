#include "metadata.h"
#include <typeinfo>
#include <fstream>
#include <dirent.h>
#include "metadata/entitynotfoundexception.h"

using namespace std;
using namespace dbjaguar;
using namespace cache;

void loadProcessDefinitions(Connection* con) {
    Logger* log = getLogger(NULL);

    if (log->isInfo()) log->info("Loading process definitions");

    CacheGroup cache = getGlobalCache("METADATA");
    ResultSet* rs = con->executeQuery("SELECT id, defname, processType, masterent FROM processdef");

    map<long, ProcessDefinition*>* mapDefinitions = new map<long, ProcessDefinition*>();
    while ((*rs)++) {
        long* id = (long*)rs->get(0);
        string* defname = (string*)rs->get(1);
        ProcessType processType = static_cast<ProcessType> (*(short int*)rs->get(2));
        string* masterent = (string*)rs->get(3);
        ProcessDefinition* def = new ProcessDefinition();
        def->setProcessType(&processType);
        //def->setProperties(vector<Property*>* _properties);
        //def->setPools(vector<Pool*>* _pools);
        def->setDefinitionName(defname);
        //void setTasks(vector<ActivityCommon*>* _tasks);
        def->setId(*id);
        //def->setEvents(vector<CommonEvent*>* _events);
        def->setMasterEntity(masterent);
        if (log->isDebug()) log->debug("Adding process definition: " + *defname);
        mapDefinitions->insert(pair<long, ProcessDefinition*>(*id, def));
    }
    cache.add("PROCESSDEFINITIONS", mapDefinitions);

    rs->close();
}

ProcessDefinition* getProcessDefinition(long id) throw (WorkflowException) {
    cache::CacheGroup group = cache::getGlobalCache("METADATA");
    map<long, ProcessDefinition*>* definitions = (map<long, ProcessDefinition*>*)group.get("PROCESSDEFINITIONS");
    if (!definitions) {
        throw new WorkflowException("The process definition does not exist");
    }
    ProcessDefinition* def =definitions->find(id)->second;
    if (!def) {
        throw new WorkflowException("The process definition does not exist");
    }
    return def;
}

void deserialize(string fileName, void** readed) {
    ifstream file;
    file.open(fileName.c_str(), ios::binary);
    file.read((char*)readed, sizeof(*readed));
    file.close();
}

void serialize(string filename, void* file) {
    ofstream ofile;
    ofile.open(filename.c_str(), ios::binary);
    ofile.write((char*)file, sizeof(file));
    ofile.close();
}

const char* EntityNotFoundException::what() const throw () {
    return message->c_str();
}


