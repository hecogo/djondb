/* 
 * File:   networkclient.h
 * Author: cross
 *
 * Created on April 12, 2010, 9:41 PM
 */

#ifndef _NETWORKCLIENT_H
#define	_NETWORKCLIENT_H

#include "net/request.h"
#include "net/response.h"

Response* sendreceive(char* host, int port, Request* req);


#endif	/* _NETWORKCLIENT_H */

