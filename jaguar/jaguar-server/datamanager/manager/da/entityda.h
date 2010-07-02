/* 
 * File:   entityda.h
 * Author: cross
 *
 * Created on May 27, 2010, 6:53 PM
 */

#ifndef _ENTITYDA_H
#define	_ENTITYDA_H

#include "../entityMD.h"
#include <map>
std::map<int, EntityMD*>* loadEntities();

void createEntity(int idEntity, int key, std::vector<int> idAttributes, std::vector<void*> values);
void updateEntity(int idEntity, int key, std::vector<int> idAttributes, std::vector<void*> values);

std::map<int, void*>* findEntityValues(int idEntity, int key);
#endif	/* _ENTITYDA_H */

