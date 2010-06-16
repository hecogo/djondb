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

SEntity* parseEntity(const char* data) {
    int len = strlen(data);
    char* entry = (char*) malloc(len + 1);
    memset(entry, 0, len);
    strcpy(entry, data);
    entry[len] = 0;
    char* entId = strtok(entry, ".");
    char* entName = strtok(NULL, ".");
    char* entType = strtok(NULL, ".");
    char* tableName = strtok(NULL, ". ");

    SEntity* entity = new SEntity();
    entity->id = atoi(entId);
    entity->name = (char*) malloc(strlen(entName) + 1);
    strcpy(entity->name, entName);
    entity->type = atoi(entType);
    entity->tableName = (char*) malloc(strlen(tableName) + 1);
    strcpy(entity->tableName, tableName);

    free(entry);
    return entity;
}

char* deployEntity(const char* data) {
    char* pointer = (char*) data;
    pointer = strchr(pointer, '{');
    int len = pointer - data;
    char* entityData = (char*) malloc(sizeof (char) * (len + 1));
    memset(entityData, 0, len);
    strncpy(entityData, data, len);
    entityData[len] = 0;
    SEntity* entity = parseEntity(entityData);
    free(entityData);
    free(strtokenizer(pointer + 1, ".")); // release the retrieved value
    char* id = strtokenizer(NULL, ".");
    char* t; // temporal reader
    while (id != NULL) {
        //.1.value.1.value.-.null.0
        SAttribute* attr = new SAttribute();
        attr->id = atoi(id);
        free(id);
        attr->name = strtokenizer(NULL, ".");
        t = strtokenizer(NULL, ".");
        attr->type = static_cast<ATTRIBUTETYPE> (atoi(t));
        free(t);
        attr->display = strtokenizer(NULL, ".-.");
        char* entRelated = strtokenizer(NULL, ".");
        if (strcmp(entRelated, "null") != 0) {
            attr->idRelatedEntity = atoi(entRelated);
        }
        free(entRelated);
        t = strtokenizer(NULL, ".");
        attr->length = atoi(t);
        free(t);
        entity->attributes.push_back(attr);
        id = strtokenizer(NULL, ".");
    }
    char* result = mysql_deployEntity(entity);
    delete(entity);
    return result;
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
        while (dataPointer[0] == '/' && dataPointer[1] == '/') {
            dataPointer = strchr(dataPointer, '\n') + 1;
        }
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
            while (dataPointer[0] == '\n') {
                dataPointer++;
            }
        } else {
            dataPointer = NULL;
        }
    }
    free(srcData);
    return "";
}
