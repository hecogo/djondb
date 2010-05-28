/* 
 * File:   attributeMD.h
 * Author: cross
 *
 * Created on May 17, 2010, 6:36 PM
 */

#ifndef _ATTRIBUTEMD_H
#define	_ATTRIBUTEMD_H

#include <string>

#include "entityMD.h"

enum ATTRIBUTETYPE {
    INT,
    BOOLEAN,
    DOUBLE,
    VARCHAR
};

class AttributeMD {
public:
    AttributeMD();
    AttributeMD(const AttributeMD& orig);
    virtual ~AttributeMD();
    void setAttributeLength(int attributeLength);
    int getAttributeLength() const;
    void setAttributeType(ATTRIBUTETYPE attributeType);
    ATTRIBUTETYPE getAttributeType() const;
    void setAttributeDisplay(std::string* attributeDisplay);
    std::string* getAttributeDisplay() const;
    void setAttributeName(std::string* attributeName);
    std::string* getAttributeName() const;
    void setIdAttribute(int idAttribute);
    int getIdAttribute() const;
    void setEntityRelated(EntityMD* _entityRelated);
    EntityMD* getEntityRelated() const;
private:
    int idAttribute;
    std::string* attributeName;
    std::string* attributeDisplay;

    ATTRIBUTETYPE attributeType;
    int attributeLength; // 0 by default

    std::string* attributeTableName;
    EntityMD* _entityRelated;
};

#endif	/* _ATTRIBUTEMD_H */

