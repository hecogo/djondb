/* 
 * File:   datamanager.h
 * Author: cross
 *
 * Created on May 17, 2010, 6:32 PM
 */

#ifndef _DATAMANAGER_H
#define	_DATAMANAGER_H

#include "manager/entityMD.h"
#include "manager/attributeMD.h"
#include "manager/entity.h"

Entity* createEntity(int idEntity);
EntityMD* getEntityMD(int id);

void loadEntitiesMD();

#endif	/* _DATAMANAGER_H */

