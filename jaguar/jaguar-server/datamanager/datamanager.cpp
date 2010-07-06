#include <sstream>

#include "manager/entity.h"
#include "manager/da/entityda.h"
#include "datamanager.h"
#include "dbjaguar.h"
#include "util.h"
#include "manager/entitiesdeploy.h"

class Transaction;

EntityMD* getEntityMD(int idEntity) {
    cache::CacheGroup* group = cache::getGlobalCache("DATAMANAGER");
    std::map<int, EntityMD*>* entities = (std::map<int, EntityMD*>*)group->get(string("ENTITYMD"));
    std::map<int, EntityMD*>::iterator iter = entities->find(idEntity);
    if (iter == entities->end()) {
        setLastError(1002, "The entity %d was not found", idEntity);
        return NULL;
    }
    return iter->second;
}

Entity* createEntity(int idEntity, Transaction* transaction) {
    EntityMD* md = getEntityMD(idEntity);

    Entity* result = new Entity(md);
    result->setTransaction(transaction);
    result->setId(getNextKey(*md->getTableName()));

    return result;
}

void loadEntitiesMD() {
    Logger* log = getLogger(NULL);

    if (log->isInfo()) log->info("Loading Entities Definitions");

    std::map<int, EntityMD*>* entities = loadEntities();
    cache::CacheGroup* group = cache::getGlobalCache("DATAMANAGER");
    group->add(string("ENTITYMD"), entities);
    
    delete(log);
}

void releaseEntitiesMD() {
    Logger* log = getLogger(NULL);

    if (log->isInfo()) log->info("Unloading Entities Definitions");

    cache::CacheGroup* group = cache::getGlobalCache("DATAMANAGER");
    std::map<int, EntityMD*>* entities = (std::map<int, EntityMD*>*)group->get(string("ENTITYMD"));
    if (entities != NULL) {
        for (std::map<int, EntityMD*>::iterator iter = entities->begin();
                iter != entities->end(); iter++) {
            delete(iter->second);
        }
    }
}

void deployEntities(std::string data) {
    char* result = deployEntities(data.c_str());
    cout << result << endl;
}

void deployEntities(std::istream *input) {
    stringbuf* ss = new stringbuf();
    while (!input->eof()) {
        (*input) >> ss;
    }

    string data = ss->str();
    deployEntities(data);
    delete(ss);
}

Entity* findEntity(int idEntity, int key) {
    TransactionManager manager;
    Transaction* trans = manager.startTransaction();
    Entity* ent = findEntity(idEntity, key, trans);
    trans->commit();
    return ent;
}

Entity* findEntity(int idEntity, int key, Transaction* transaction) {
    Entity* ent;
    map<int, void*>* values = findEntityValues(idEntity, key);
    if (values) {
        EntityMD* entMD = getEntityMD(idEntity);
        ent = new Entity(entMD, *values);
        ent->setTransaction(transaction);
    } else {
        ent = NULL;
    }
    return ent;
}
