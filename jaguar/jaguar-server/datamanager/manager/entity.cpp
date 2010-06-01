/* 
 * File:   Entity.cpp
 * Author: cross
 * 
 * Created on May 17, 2010, 6:33 PM
 */

#include "entity.h"
#include "entityMD.h"
#include "attributeMD.h"
#include "util.h"
#include "../datamanager.h"
#include <stdlib.h>

Entity::Entity(EntityMD* entityMD) {
    _entityMd = entityMD;
}

Entity::Entity(const Entity& orig) {
    _attributeValues = orig._attributeValues;
    _entityMd = orig._entityMd;
    _transaction = orig._transaction;
}

Entity::~Entity() {
}

void Entity::setValue(const char* xpath, void* value) {
    int index;
    char* prop = nextProp(xpath, index);
    AttributeMD* attribute = _entityMd->getAttributeMD(prop);
    if (attribute == NULL) {
        setLastError(1002, "The attribute '%s' was not found in the entity '%s'", prop, _entityMd->getEntityName()->c_str());
        free(prop);
        return;
    }
    free(prop);
    void* currentValue = _attributeValues[*attribute->getAttributeName()];
    void* transactionValue = _transaction->getValue(_entityMd->getIdEntity(), attribute->getIdAttribute(), id);
    if (transactionValue != NULL) {
        currentValue = transactionValue;
    }
    if (index > -1) {
        EntityMD* relatedEntityMD = attribute->getEntityRelated();
        if (relatedEntityMD == NULL) {
            setLastError(1001, "the property %s is not related to an entity, the xpath %s is not valid", prop, xpath);
            return;
        }
        Entity* entity = (Entity*) currentValue;
        if (entity == NULL) {
            entity = createEntity(relatedEntityMD->getIdEntity(), _transaction);
            entity->setTransaction(_transaction);
            _transaction->addEntry(_entityMd->getIdEntity(), attribute->getIdAttribute(), getId(), entity);
        }
        entity->setValue(xpath + index + 1, value);
    } else {
        _transaction->addEntry(_entityMd->getIdEntity(), attribute->getIdAttribute(), getId(), value);
    }
}

void* Entity::getValue(const char* xpath) {
    int index;
    char* prop = nextProp(xpath, index);
    AttributeMD* attribute = _entityMd->getAttributeMD(prop);
    free(prop);
    if (attribute == NULL) {
        // The error code is in LastError
        return NULL;
    }
    void* currentValue = _attributeValues[*attribute->getAttributeName()];
    void* transactionValue = _transaction->getValue(_entityMd->getIdEntity(), attribute->getIdAttribute(), id);
    if (transactionValue != NULL) {
        currentValue = transactionValue;
    }
    if (currentValue == NULL) {
        return NULL;
    }
    if (index > -1) {
        EntityMD* relatedEntityMD = attribute->getEntityRelated();
        if (relatedEntityMD == NULL) {
            setLastError(1001, "the property %s is not related to an entity, the xpath %s is not valid", prop, xpath);
            return NULL;
        }
        Entity* entity = (Entity*) currentValue;
        return entity->getValue(xpath + index + 1);
    } else {
        return currentValue;
    }
}

AttributeMD* Entity::getAttributeMD(const char* xpath) {
    AttributeMD* attribute = _entityMd->getAttributeMD(xpath);
    return attribute;
}

void Entity::setTransaction(Transaction* transaction) {
    _transaction = transaction;
}

void Entity::setId(int id) {
    this->id = id;
}

int Entity::getId() const {
    return id;
}