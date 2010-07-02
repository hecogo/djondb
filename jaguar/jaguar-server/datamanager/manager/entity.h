/* 
 * File:   entity.h
 * Author: cross
 *
 * Created on May 17, 2010, 6:33 PM
 */

#ifndef _ENTITY_H
#define	_ENTITY_H

#include <map>
#include <string>

#include "transaction/transaction.h"

using namespace std;

class EntityMD;
class AttributeMD;
class Transaction;

class Entity {
public:
    Entity(EntityMD* entityMD);
    Entity(const Entity& orig);
    Entity(EntityMD* entityMD, map<int, void*> values);
    virtual ~Entity();
    int setValue(const char* xpath, void* value);
    void* getValue(const char* xpath);
    AttributeMD* getAttributeMD(const char* xpath);
    void setTransaction(Transaction* transaction);
    void setId(int id);
    int getId() const;

private:
    EntityMD* _entityMd;
    int id;
    map<string, void*> _attributeValues;
    Transaction* _transaction;

    void loadValues(map<int, void*> values);
    int checkType(AttributeMD* attributeMD, void* value);
};

#endif	/* _ENTITY_H */

