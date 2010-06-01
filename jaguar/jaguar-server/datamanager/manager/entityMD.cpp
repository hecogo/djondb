/* 
 * File:   EntityMD.cpp
 * Author: cross
 * 
 * Created on May 17, 2010, 6:33 PM
 */

#include <string.h>
#include <stdlib.h>
#include "entityMD.h"
#include "util.h"
#include "attributeMD.h"

EntityMD::EntityMD() {
}

void EntityMD::setAttributesMD(std::vector<AttributeMD*>* _attributesMD) {
    this->_attributesMD = _attributesMD;
}

std::vector<AttributeMD*>* EntityMD::getAttributesMD() const {
    return _attributesMD;
}

AttributeMD* EntityMD::getAttributeMD(const char* xpath) const {
    Logger* log = getLogger(NULL);
    int index;
    char* prop = nextProp(xpath, index);
    vector<AttributeMD*>::iterator iter = _attributesMD->begin();
    AttributeMD* attribute = NULL;
    while (iter != _attributesMD->end()) {
        const char* attrName = (*iter)->getAttributeName()->c_str();
        if (strcasecmp(prop, attrName) == 0) {
            attribute = *iter;
            break;
        }
        iter++;
    }
    if (index > -1) {
        EntityMD* relatedEntity = attribute->getEntityRelated();
        if (relatedEntity == NULL) {
            setLastError(1001, "the property %s is not related to an entity, the xpath %s is not valid", prop, xpath);
            delete(log);
            free(prop);
            return NULL;
        }
        attribute = relatedEntity->getAttributeMD(xpath + index + 1);
    }
    if (attribute == NULL) {
        setLastError(1002, "The xpath: %s is not valid from the Entity: %s", xpath, getEntityName()->c_str());
        delete(log);
        return NULL;
    }
    delete(log);
    return attribute;
}

void EntityMD::setTableName(std::string* _tableName) {
    this->_tableName = _tableName;
}

std::string* EntityMD::getTableName() const {
    return _tableName;
}

void EntityMD::setEntityType(ENTITY_TYPE _entityType) {
    this->_entityType = _entityType;
}

ENTITY_TYPE EntityMD::getEntityType() const {
    return _entityType;
}

void EntityMD::setEntityName(std::string* _entityName) {
    this->_entityName = _entityName;
}

std::string* EntityMD::getEntityName() const {
    return _entityName;
}

void EntityMD::setIdEntity(int _idEntity) {
    this->_idEntity = _idEntity;
}

int EntityMD::getIdEntity() const {
    return _idEntity;
}

EntityMD::EntityMD(const EntityMD& orig) {
}

EntityMD::~EntityMD() {
}

