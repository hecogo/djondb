#include "manager/entity.h"
#include "manager/da/entityda.h"
#include "datamanager.h"
#include "dbjaguar.h"
#include "util.h"

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

Entity* createEntity(int idEntity) {
    EntityMD* md = getEntityMD(idEntity);
    
    Entity* result = new Entity(md);
    result->setId(getNextKey(*md->getTableName()));

    return result;
}

void loadEntitiesMD() {
    std::map<int, EntityMD*>* entities = loadEntities();
    cache::CacheGroup* group = cache::getGlobalCache("DATAMANAGER");
    group->add(string("ENTITYMD"), entities);
}