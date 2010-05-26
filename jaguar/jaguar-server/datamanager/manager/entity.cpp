/* 
 * File:   Entity.cpp
 * Author: cross
 * 
 * Created on May 17, 2010, 6:33 PM
 */

#include "entity.h"
#include "entityMD.h"

Entity::Entity() {
}

Entity::Entity(const Entity& orig) {
}

Entity::~Entity() {
}

void Entity::setValue(const char* xpath, void* value) {
}

void* Entity::getValue(const char* xpath) {
}

AttributeMD* Entity::getAttributeMD(const char* xpath) {
    _entityMd->getAttributesMD(xpath);
    return NULL;
}

void Entity::setTransaction(Transaction* transaction) {
    _transaction = transaction;
}