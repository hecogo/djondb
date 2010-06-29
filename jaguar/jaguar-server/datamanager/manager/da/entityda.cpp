
#include "entityda.h"
#include "dbjaguar.h"
#include "../entityMD.h"
#include "../attributeMD.h"
#include "../../datamanager.h"
#include "util.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace dbjaguar;

void loadAttributes(EntityMD* entMD, std::map<int, EntityMD*>* entities) {
    std::vector<AttributeMD*>* loaded = new std::vector<AttributeMD*>();

    Connection* conn = getDefaultMDConnection();
    std::stringstream sql;
    sql << "SELECT * FROM attributes where idEntity = " << entMD->getIdEntity();

    ResultSet* rs = conn->executeQuery(sql.str().c_str());
    while (rs->next()) {
        int* id = static_cast<int*> (rs->get("id"));
        AttributeMD* attrMD = new AttributeMD();
        attrMD->setIdAttribute(*id);
        attrMD->setAttributeName(static_cast<string*> (rs->get("attrname")));
        ATTRIBUTETYPE type = (ATTRIBUTETYPE)*(static_cast<int*> (rs->get("attrtype")));
        attrMD->setAttributeType(type);
        attrMD->setAttributeDisplay(static_cast<string*> (rs->get("attrdisplay")));
        int* attrLength = static_cast<int*> (rs->get("attrlength"));
        if (attrLength != NULL) {
            attrMD->setAttributeLength(*attrLength);
        }
        int* idEntityRelated = static_cast<int*> (rs->get("identityrelated"));
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

    rs->close();
    delete(rs);
    conn->close();
    delete(conn);

    entMD->setAttributesMD(loaded);
}

std::map<int, EntityMD*>* loadEntities() {
    std::map<int, EntityMD*>* entities = new std::map<int, EntityMD*>();
    Connection* conn = getDefaultMDConnection();
    ResultSet* rs = conn->executeQuery("SELECT * FROM entities");
    while (rs->next()) {
        int* id = static_cast<int*> (rs->get("id"));
        EntityMD* entMD = new EntityMD();
        entMD->setIdEntity(*id);
        string* entName = static_cast<string*> (rs->get("entname"));
        entMD->setEntityName(entName);
        int* iType = static_cast<int*> (rs->get("enttype"));
        ENTITY_TYPE type = (ENTITY_TYPE) * iType;
        entMD->setEntityType(type);
        entMD->setTableName(static_cast<string*> (rs->get("enttablename")));
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

void saveEntityMD(EntityMD* entityMD) {
    //    Connection* conn = getDefaultMDConnection();
    //
    //    conn->createStatement()
    //    conn->close();
    //    delete(conn);
}

bool entityExist(EntityMD* entityMD, int key) {
    Connection* conn = getDefaultDataConnection();
    stringstream sql;
    sql << "SELECT id FROM " << *entityMD->getTableName() << " WHERE id = " << key;
    ResultSet* rs = conn->executeQuery(sql.str().c_str());
    bool exist = false;
    if (rs->next()) {
        exist = true;
    };
    rs->close();
    delete(rs);
    conn->close();
    delete(conn);
    return exist;
}

void saveEntityData(int idEntity, int key, std::vector<int> idAttributes, std::vector<void*> values) {
    Logger* log = getLogger(NULL);

    EntityMD* entityMD = getEntityMD(idEntity);

    bool exist = entityExist(entityMD, key);

    stringstream ss;
    ss << "Entity Id: " << entityMD->getIdEntity() << ", Key: " << key << " exist: " << exist;
    log->debug(ss.str());

    std::vector<int>::iterator iterAttrib = idAttributes.begin();

    stringstream insertSQLcolumns;
    insertSQLcolumns << "INSERT INTO " << *entityMD->getTableName() << " (id, ";
    stringstream insertSQLvalues;
    insertSQLvalues << ") VALUES (?, ";
    while (iterAttrib != idAttributes.end()) {
        int idAttrib = *iterAttrib;
        AttributeMD* attrMD = entityMD->getAttributeMD(idAttrib);
        insertSQLcolumns << *attrMD->getAttributeName() << ", ";
        insertSQLvalues << "?, ";
        iterAttrib++;
    }
    string sql = insertSQLcolumns.str();
    size_t pos = sql.rfind(", ");
    sql.erase(sql.begin() + pos, sql.end());

    string sqlvalues = insertSQLvalues.str();
    pos = sqlvalues.rfind(", ");
    sql.append(sqlvalues.begin(), sqlvalues.begin() + pos);
    sql.append(")");

    Connection* con = getDefaultDataConnection();
    Statement* stm = con->createStatement(sql.c_str());

    stm->setParameter(0, DBTYPE_LONG, &key);
    int param = 1;
    iterAttrib = idAttributes.begin();
    for (std::vector<void*>::iterator iterValues = values.begin(); iterValues != values.end(); iterValues++) {
        void* value = *iterValues;
        AttributeMD* attrMD = entityMD->getAttributeMD(*iterAttrib);
        DBFIELD_TYPE type;
        switch (attrMD->getAttributeType()) {
            case AT_INT:
                type = DBTYPE_LONG;
                break;
            case AT_BOOLEAN:
                type = DBTYPE_SHORT;
                break;
            case AT_DOUBLE:
                type = DBTYPE_DOUBLE;
                break;
            case AT_VARCHAR:
                type = DBTYPE_STRING;
                if (value != NULL) {
                    string* sval = (string*)value;
                    value = (void*)sval->c_str();
                }
                break;
        }
        if ((attrMD->getEntityRelated() != NULL) && (value != NULL)) {
            Entity* entRelated = (Entity*)value;
            value = (void*)new int(entRelated->getId());
        }
        stm->setParameter(param, type, value);
        iterAttrib++;
        param++;
    }
    int rowsUpdated = stm->executeUpdate();
    stm->close();
    delete(stm);
    con->close();
    delete(con);
    delete(log);
}