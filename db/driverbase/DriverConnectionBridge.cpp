/*
 * =====================================================================================
 *
 *       Filename:  DriverConnectionBridge.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/11/2012 09:53:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
		DriverConnectionBridge(Connection* connection);
		DriverConnectionBridge(const DriverConnectionBridge& orig);
		virtual ~DriverConnectionBridge();

	public:
		virtual void insert(std::string ns, const BSONObj& bson);
		virtual void update(std::string ns, const BSONObj& bson);
		virtual std::vector<BSONObj*>* find(std::string ns, const BSONObj& filter);
		virtual BSONObj* findByKey(std::string ns, std::string id);
	
