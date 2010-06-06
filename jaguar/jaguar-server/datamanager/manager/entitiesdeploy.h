/* 
 * File:   entitisdeploy.h
 * Author: cross
 *
 * Created on June 2, 2010, 1:15 PM
 */

#ifndef _ENTITISDEPLOY_H
#define	_ENTITISDEPLOY_H

#include <string>
#include <vector>
#include "attributeMD.h"

struct SAttribute {
    int id;
    const char* name;
    ATTRIBUTETYPE type;
    const char* display;
    int idRelatedEntity;
    int length;
};

struct SEntity {
    int id;
    const char* name;
    int type;
    const char* tableName;
    std::vector<SAttribute*> attributes;
};

char* deployEntities(const char* data);

#endif	/* _ENTITISDEPLOY_H */

