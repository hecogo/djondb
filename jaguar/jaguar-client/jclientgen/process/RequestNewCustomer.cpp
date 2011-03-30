/* 
 * File:   RequestNewCustomer.cpp
 * Author: cross
 * 
 * Created on November 21, 2010, 6:57 PM
 */

#include "RequestNewCustomer.h"

RequestNewCustomer::RequestNewCustomer()
 : Request(2) {
}

RequestNewCustomer::RequestNewCustomer(const RequestNewCustomer& orig)
: Request(orig) {
}

RequestNewCustomer::~RequestNewCustomer() {
}

