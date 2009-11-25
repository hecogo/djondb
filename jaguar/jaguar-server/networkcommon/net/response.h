/* 
 * File:   Response.h
 * Author: cross
 *
 * Created on November 24, 2009, 9:33 PM
 */

#ifndef _RESPONSE_H
#define	_RESPONSE_H

#include <string>

using namespace std;

class Response {
public:
    Response(string* data);
    string* getData();
    void addParameter(char* name, void* contents, int size);
    virtual ~Response();
private:
    string* data;
};

#endif	/* _RESPONSE_H */

