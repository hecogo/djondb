/*
 * =====================================================================================
 *
 *       Filename:  settings.h
 *
 *    Description:  Settings file, this will control the settings of djondb
 *
 *        Version:  1.0
 *        Created:  02/23/2012 09:37:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Juan Pablo Crossley (crossleyjuan@gmail.com)
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef INCLUDE_SETTINGS_H
#define INCLUDE_SETTINGS_H

class Settings {
	public:
		Settings();
		virtual ~Settings();
		Settings(const Settings& orig);

		char* databaseFolder() const;

	private:
		char* _databaseFolder;

};

Settings getSettings();

#endif // INCLUDE_SETTINGS_H
