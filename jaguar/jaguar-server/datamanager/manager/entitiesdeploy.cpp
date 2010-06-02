#include "entitiesdeploy.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

char* deployEntity(const char* data) {
    cout << "deploy: " << data << endl;
}

char* deployEntities(const char* data) {
    int len = strlen(data);
    char* srcData = (char*) malloc(len);
    // Copy the source data
    memset(srcData, 0, len);
    strcpy(srcData, data);
    // pointer to the current data to analize
    const char* dataPointer = srcData;
    while (dataPointer != NULL) {
        const char* tmpData = strchr(dataPointer, '}');
        if (tmpData != NULL) {
            int tmpLen = tmpData - dataPointer + 1;
            char* entityData = (char*) malloc(tmpLen);
            memset(entityData, 0, tmpLen);
            strncpy(entityData, dataPointer, tmpLen);
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
