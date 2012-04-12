/*
 * =====================================================================================
 *
 *       Filename:  DriverConnectionBridge.h
 *
 *    Description:  Implementation of the ConnectionBridge at driver level
 *                  This class will redirect all the calls to the driver connection
 *
 *        Version:  1.0
 *        Created:  04/11/2012 09:53:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Juan Pablo Crossley (crossleyjuan@gmail.com), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef DRIVERCONNECTIONBRIDGE_INCLUDED_H
#define DRIVERCONNECTIONBRIDGE_INCLUDED_H

#include "connectionbridge.h"
#include "bson.h"

#include <string>
#include <vector>

class Connection;

class DriverConnectionBridge: public ConnectionBridge {

	public:
		DriverConnectionBridge(Connection* connection);
		DriverConnectionBridge(const DriverConnectionBridge& orig);
		virtual ~DriverConnectionBridge();

	public:
		virtual void insert(std::string ns, const BSONObj& bson);
		virtual void update(std::string ns, const BSONObj& bson);
		virtual std::vector<BSONObj*>* find(std::string ns, const BSONObj& filter);
		virtual BSONObj* findByKey(std::string ns, std::string id);
	
	private:
		Connection* _connection;
};

#endif // DRIVERCONNECTIONBRIDGE_INCLUDED_H
