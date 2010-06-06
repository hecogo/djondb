#include "entitiesdeploy.h"
#include "da/mysqlentitydeploy.h"
#include "entity.h"
#include "util.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

//.1.request.1.request {
//.1.value.1.value.-.null.0
//}

SEntity* parseEntity(char* data) {
    char* entId = strtok(data, ".");
    char* entName = strtok(NULL, ".");
    char* entType = strtok(NULL, ".");
    char* tableName = strtok(NULL, ".");

    SEntity* entity = new SEntity();
    entity->id = atoi(entId);
    entity->name = entName;
    entity->type = atoi(entType);
    entity->tableName = tableName;

    return entity;
}

char* deployEntity(const char* data) {
    char* pointer = (char*) data;
    pointer = strchr(pointer, '{');
    int len = pointer - data;
    char* entityData = (char*) malloc(len + 1);
    memset(entityData, 0, len);
    memcpy(entityData, data, len);
    entityData[len] = 0;
    SEntity* entity = parseEntity(entityData);
    strtok(pointer + 1, ".");
    char* id = strtok(NULL, ".");
    while (id != NULL) {
        //.1.value.1.value.-.null.0
        SAttribute* attr = new SAttribute();
        attr->id = atoi(id);
        attr->name = strtok(NULL, ".");
        attr->type = static_cast<ATTRIBUTETYPE> (atoi(strtok(NULL, ".")));
        attr->display = strtok(NULL, ".");
        const char* entRelated = strtok(NULL, ".");
        if (strcmp(entRelated, "null") != 0) {
            attr->idRelatedEntity = atoi(entRelated);
        }
        attr->length = atoi(strtok(NULL, "."));
        entity->attributes.push_back(attr);
        id = strtok(NULL, ".");
    }
    free(entityData);
    return mysql_deployEntity(entity);
}

char* deployEntities(const char* data) {
    int len = strlen(data);
    char* srcData = (char*) malloc(len + 1);
    // Copy the source data
    memset(srcData, 0, len);
    memcpy(srcData, data, len);
    srcData[len] = 0;
    // pointer to the current data to analize
    const char* dataPointer = srcData;
    while (dataPointer != NULL) {
        const char* tmpData = strchr(dataPointer, '}');
        if (tmpData != NULL) {
            int tmpLen = tmpData - dataPointer + 1;
            char* entityData = (char*) malloc(tmpLen + 1);
            memset(entityData, 0, tmpLen);
            memcpy(entityData, dataPointer, tmpLen);
            entityData[tmpLen] = 0;
            deployEntity(entityData);

            free(entityData);
            dataPointer = tmpData + 1;
        } else {
            dataPointer = NULL;
        }
    }
    free(srcData);
    return "";
}
