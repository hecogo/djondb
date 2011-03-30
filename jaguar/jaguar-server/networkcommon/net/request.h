/* 
 * File:   Request.h
 * Author: cross
 *
 * Created on November 24, 2009, 8:23 PM
 */

#ifndef _REQUEST_H
#define	_REQUEST_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Request {
public:
    Request(int type);
    Request(const Request& orig);
    virtual ~Request();
    Request(const char* data);
    void addParameter(string codename, string* value);
    int getType();
    string* getParameter(string codename);
    vector<string>* getCodeNames();

    const char* toCharArray();
    void loadFrom(const char* data);
private:
    int _type;
    map<string, string*>* _parameters;

    char* getData(const char* data, int offset, int size);
};

#endif	/* _REQUEST_H */

