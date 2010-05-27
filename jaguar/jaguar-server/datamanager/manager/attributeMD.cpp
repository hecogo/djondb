/* 
 * File:   attributeMD.cpp
 * Author: cross
 * 
 * Created on May 17, 2010, 6:36 PM
 */

#include "attributeMD.h"

AttributeMD::AttributeMD() {
}

void AttributeMD::setAttributeTableName(std::string* attributeTableName) {
    this->attributeTableName = attributeTableName;
}

std::string* AttributeMD::getAttributeTableName() const {
    return attributeTableName;
}

void AttributeMD::setAttributeLength(int attributeLength) {
    this->attributeLength = attributeLength;
}

int AttributeMD::getAttributeLength() const {
    return attributeLength;
}

void AttributeMD::setAttributeType(ATTRIBUTETYPE attributeType) {
    this->attributeType = attributeType;
}

ATTRIBUTETYPE AttributeMD::getAttributeType() const {
    return attributeType;
}

void AttributeMD::setAttributeDisplay(std::string* attributeDisplay) {
    this->attributeDisplay = attributeDisplay;
}

std::string* AttributeMD::getAttributeDisplay() const {
    return attributeDisplay;
}

void AttributeMD::setAttributeName(std::string* attributeName) {
    this->attributeName = attributeName;
}

std::string* AttributeMD::getAttributeName() const {
    return attributeName;
}

void AttributeMD::setIdAttribute(int idAttribute) {
    this->idAttribute = idAttribute;
}

int AttributeMD::getIdAttribute() const {
    return idAttribute;
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
}

