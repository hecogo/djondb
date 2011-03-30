/* 
 * File:   RequestNewCustomer.h
 * Author: cross
 *
 * Created on November 21, 2010, 6:57 PM
 */

#ifndef REQUESTNEWCUSTOMER_H
#define	REQUESTNEWCUSTOMER_H

#include "net/request.h"

class RequestNewCustomer: public Request {
public:
    RequestNewCustomer();
    RequestNewCustomer(const RequestNewCustomer& orig);
    virtual ~RequestNewCustomer();
private:

};

#endif	/* REQUESTNEWCUSTOMER_H */

