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
    void setAttributesMD(std::vector<AttributeMD*>* _attributesMD);
    std::vector<AttributeMD*>* getAttributesMD() const;
    AttributeMD* getAttributeMD(const char* xpath) const;
    AttributeMD* getAttributeMD(int idAttrib) const;
    void setTableName(std::string* _tableName);
    std::string* getTableName() const;
    void setEntityType(ENTITY_TYPE _entityType);
    ENTITY_TYPE getEntityType() const;
    void setEntityName(std::string* _entityName);
    std::string* getEntityName() const;
    void setIdEntity(int _idEntity);
    int getIdEntity() const;

private:
// Entity Metadata
    int _idEntity;
    std::string* _entityName;
    ENTITY_TYPE _entityType;
    
// Entity Table information
    std::string* _tableName;

// Attributes Information
    std::vector<AttributeMD*>* _attributesMD;

};

#endif	/* _EntityMD_H */

