/*
 * =====================================================================================
 *
 *       Filename:  ConnectionBridge.h
 *
 *    Description:  Defines the common connection bridge used in transactions, replication
 *                  and other operations that requires to change a Driver managed Connection 
 *                  or use a DBController directly
 *
 *        Version:  1.0
 *        Created:  04/11/2012 09:45:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CONNECTIONBRIDGE_INCLUDED_H
#define CONNECTIONBRIDGE_INCLUDED_H

class ConnectionBridge {

	public:
		virtual void insert(std::string ns, const BSONObj& bson) = 0;
		virtual void update(std::string ns, const BSONObj& bson) = 0;
		virtual std::vector<BSONObj*>* find(std::string ns, const BSONObj& filter) = 0;
		virtual BSONObj* findByKey(std::string ns, std::string id) = 0;
};

#endif // CONNECTIONBRIDGE_INCLUDED_H
