/* 
 * File:   EntityMD.cpp
 * Author: cross
 * 
 * Created on May 17, 2010, 6:33 PM
 */

#include "entityMD.h"

EntityMD::EntityMD() {
}
void EntityMD::setAttributesMD(std::vector<AttributeMD>* _attributesMD) {
    this->_attributesMD = _attributesMD;
}
std::vector<AttributeMD>* EntityMD::getAttributesMD() const {
    return _attributesMD;
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

