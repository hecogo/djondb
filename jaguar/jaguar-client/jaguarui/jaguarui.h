/* 
 * File:   jaguarui.h
 * Author: cross
 *
 * Created on February 24, 2010, 10:45 PM
 */

#ifndef _JAGUARUI_H
#define	_JAGUARUI_H

#include "ScreenBase.h"
#include "ui/MenuItem.h"
#include <vector>

typedef ScreenBase* (*screenFunction)();

void addScreen(screenFunction function, char* menu);

std::vector<MenuItem*> getMenuItems();
ScreenBase* callScreenFunction(int id);

#endif	/* _JAGUARUI_H */

