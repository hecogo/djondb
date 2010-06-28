/* 
 * File:   entityda.h
 * Author: cross
 *
 * Created on May 27, 2010, 6:53 PM
 */

#ifndef _ENTITYDA_H
#define	_ENTITYDA_H

#include <map>
#include "../entityMD.h"
std::map<int, EntityMD*>* loadEntities();

void saveEntityData(int idEntity, int key, std::vector<int> idAttributes, std::vector<void*> values);
#endif	/* _ENTITYDA_H */

