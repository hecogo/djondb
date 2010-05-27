


#include "manager/entity.h"
#include "datamanager.h"
#include "dbjaguar.h"


EntityMD* getEntityMD(int idEntity) {
    aqui voy!
    cache::globalCache->get("ENTITYMD");
}

Entity* createEntity(int idEntity) {
    EntityMD* md = getEntityMD(idEntity);
    
    Entity* result = new Entity(md);
    result->setId(getNextKey(*md->getTableName()));

    return result;
}
