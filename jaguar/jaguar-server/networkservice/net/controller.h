#ifndef _CONTROLLER_H
#define	_CONTROLLER_H

#include <map>

using namespace std;

class Request;
class Response;
class Controller;

extern map<int, Controller*> m_controllers;

Controller* findController(Request* request);

class Controller {
protected:
    int requestType;
public:
    Controller(int requestType);
    virtual ~Controller();
    int getRequestType();
    void selfRegister();
    virtual Response* processRequest(Request* req) = 0;
};

#endif	/* _CONTROLLER_H */

