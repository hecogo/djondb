/* 
 * File:   attributeMD.cpp
 * Author: cross
 * 
 * Created on May 17, 2010, 6:36 PM
 */

#include "attributeMD.h"

AttributeMD::AttributeMD() {
    _attributeDisplay = NULL;
    _attributeName = NULL;
    _attributeTableName = NULL;
}

void AttributeMD::setAttributeLength(int attributeLength) {
    this->_attributeLength = attributeLength;
}

int AttributeMD::getAttributeLength() const {
    return _attributeLength;
}

void AttributeMD::setAttributeType(ATTRIBUTETYPE attributeType) {
    this->_attributeType = attributeType;
}

ATTRIBUTETYPE AttributeMD::getAttributeType() const {
    return _attributeType;
}

void AttributeMD::setAttributeDisplay(std::string* attributeDisplay) {
    this->_attributeDisplay = attributeDisplay;
}

std::string* AttributeMD::getAttributeDisplay() const {
    return _attributeDisplay;
}

void AttributeMD::setAttributeName(std::string* attributeName) {
    this->_attributeName = attributeName;
}

std::string* AttributeMD::getAttributeName() const {
    return _attributeName;
}

void AttributeMD::setIdAttribute(int idAttribute) {
    this->_idAttribute = idAttribute;
}

int AttributeMD::getIdAttribute() const {
    return _idAttribute;
}
void AttributeMD::setEntityRelated(EntityMD* _entityRelated) {
    this->_entityRelated = _entityRelated;
}
EntityMD* AttributeMD::getEntityRelated() const {
    return _entityRelated;
}

AttributeMD::AttributeMD(const AttributeMD& orig) {
}

AttributeMD::~AttributeMD() {
    if (_attributeDisplay) delete(_attributeDisplay);
    if (_attributeName) delete(_attributeName);
    if (_attributeTableName) delete(_attributeTableName);
}

