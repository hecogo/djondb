/*
 * =====================================================================================
 *
 *       Filename:  Settings.cpp
 *
 *    Description:  Implementation of Settings
 *
 *        Version:  1.0
 *        Created:  02/23/2012 09:41:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Juan Pablo Crossley (crossleyjuan@gmail.com), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "settings.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

Settings::Settings() {

}

Settings::~Settings() {
	free(_databaseFolder);
}

Settings::Settings(const Settings& orig) {
	this->_databaseFolder = orig._databaseFolder;
}

char* Settings::databaseFolder() const {

}

Settings getSettings() {
	Settings settings;
	std::ifstream f;	
}

