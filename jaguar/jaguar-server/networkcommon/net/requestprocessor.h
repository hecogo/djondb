/* 
 * File:   RequestProcessor.h
 * Author: cross
 *
 * Created on November 24, 2009, 8:21 PM
 */

#ifndef _REQUESTPROCESSOR_H
#define	_REQUESTPROCESSOR_H

class Response;
class Request;

class RequestProcessor {
public:
    RequestProcessor();
    virtual ~RequestProcessor();
    Response* processRequest(Request* request);
private:

};

#endif	/* _REQUESTPROCESSOR_H */

