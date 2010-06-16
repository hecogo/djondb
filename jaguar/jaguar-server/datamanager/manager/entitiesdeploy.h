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
#include <stdlib.h>

struct SAttribute {
    int id;
    char* name;
    ATTRIBUTETYPE type;
    char* display;
    int idRelatedEntity;
    int length;

    ~SAttribute() {
        if (name) free(name);
        if (display) free(display);
    }
};

struct SEntity {
    int id;
    char* name;
    int type;
    char* tableName;
    std::vector<SAttribute*> attributes;

    ~SEntity() {
        if (name) free(name);
        if (tableName) free(tableName);
        for (std::vector<SAttribute*>::iterator iter = attributes.begin(); iter != attributes.end(); iter++) {
            delete(*iter);
        }
    }
};

char* deployEntities(const char* data);

#endif	/* _ENTITISDEPLOY_H */

