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
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
    void setValue(const char* xpath, void* value);
    void* getValue(const char* xpath);
    AttributeMD* getAttributeMD(const char* xpath);
    void setTransaction(Transaction* transaction);

private:
    EntityMD* _entityMd;
    int id;
    map<string, void**> _attributeValues;
    Transaction* _transaction;

};

#endif	/* _ENTITY_H */

