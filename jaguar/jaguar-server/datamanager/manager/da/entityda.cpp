
#include "entityda.h"
#include "dbjaguar.h"
#include "../entityMD.h"
#include "../attributeMD.h"
#include "util.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace dbjaguar;

void loadAttributes(EntityMD* entMD, std::map<int, EntityMD*>* entities) {
    std::vector<AttributeMD*>* loaded = new std::vector<AttributeMD*>();

    Connection* conn = getDefaultMDConnection();
    std::stringstream sql;
    sql << "SELECT * FROM attributes where idEntity = " << entMD->getIdEntity();
    
    ResultSet* rs = conn->executeQuery(sql.str().c_str());
    while (rs->next()) {
        int* id = static_cast<int*>(rs->get("id"));
        AttributeMD* attrMD = new AttributeMD();
        attrMD->setIdAttribute(*id);
        attrMD->setAttributeName(static_cast<string*>(rs->get("attrname")));
        ATTRIBUTETYPE type = (ATTRIBUTETYPE)*(static_cast<int*>(rs->get("attrtype")));
        attrMD->setAttributeType(type);
        attrMD->setAttributeDisplay(static_cast<string*>(rs->get("attrdisplay")));
        int* attrLength = static_cast<int*>(rs->get("attrlength"));
        if (attrLength != NULL) {
            attrMD->setAttributeLength(*attrLength);
        }
        int* idEntityRelated = static_cast<int*>(rs->get("identityrelated"));
        if (idEntityRelated != NULL) {
            map<int, EntityMD*>::iterator iter = entities->find(*idEntityRelated);
            if (iter == entities->end()) {
                setLastError(1002, "Entity not found, the idEntityRelated contains an invalid value. idEntity: %d, idAttrib: %d, idEntityRelated: %d ", entMD->getIdEntity(), *id, *idEntityRelated);
                return;
            }
            attrMD->setEntityRelated(iter->second);
        }
        loaded->push_back(attrMD);
    }
    entMD->setAttributesMD(loaded);
}

std::map<int, EntityMD*>* loadEntities() {
    std::map<int, EntityMD*>* entities = new std::map<int, EntityMD*>();
    Connection* conn = getDefaultMDConnection();
    ResultSet* rs = conn->executeQuery("SELECT * FROM entities");
    while (rs->next()) {
        int* id = static_cast<int*>(rs->get("id"));
        EntityMD* entMD = new EntityMD();
        entMD->setIdEntity(*id);
        string* entName = static_cast<string*>(rs->get("entname"));
        entMD->setEntityName(entName);
        int* iType = static_cast<int*>(rs->get("enttype"));
        ENTITY_TYPE type = (ENTITY_TYPE)*iType;
        entMD->setEntityType(type);
        entMD->setTableName(static_cast<string*>(rs->get("enttablename")));
        entities->insert(pair<int, EntityMD*>(*id, entMD));
    }

    rs->close();
    delete(rs);
    conn->close();
    delete(conn);
    
    for (std::map<int, EntityMD*>::iterator iter = entities->begin(); iter != entities->end(); iter++) {
        EntityMD* entMD = iter->second;
        loadAttributes(entMD, entities);
    }

    return entities;
}
