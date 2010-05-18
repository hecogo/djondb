/* 
 * File:   EntityMD.h
 * Author: cross
 *
 * Created on May 17, 2010, 6:33 PM
 */

#ifndef _EntityMD_H
#define	_EntityMD_H

#include <string>
#include <vector>

class AttributeMD;

enum ENTITY_TYPE {
    NORMAL,
    BASIC,
    SYSTEM
};

class EntityMD {
public:
    EntityMD();
    EntityMD(const EntityMD& orig);
    virtual ~EntityMD();

    int getId();
    
private:
// Entity Metadata
    int _idEntity;
    std::string* _entityName;
    ENTITY_TYPE _entityType;
    
// Entity Table information
    std::string* _tableName;

// Attributes Information
    std::vector<AttributeMD>* _attributesMD;

};

#endif	/* _EntityMD_H */

