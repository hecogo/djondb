#include <string>
#include <map>
#include <vector>

using namespace std;

class NetworkException : public exception {
private:
    string *message;
public:

    NetworkException(string *_message) {
        message = _message;
    }

    virtual const char* what() const throw () {
        return message->c_str();
    }
};

class Response {
private:
    string* data;
public:
    Response(string* data);
    string* getData();
    void addParameter(char* name, void* contents, int size);
};

class Request {
private:
    int type;
    map<string, string*>* parameters;
//friend:
public:
    Request(const char* data);
    void addParameter(string codename, string* value);
    int getType();
    string* getParameter(string codename);
    vector<string>* getCodeNames();
};

class RequestProcessor {
public:
    Response* processRequest(Request* request);
};

class Controller {
protected:
    int requestType;
public:
    Controller(int requestType);
    int getRequestType();
    virtual Response* processRequest(Request* request);
    void selfRegister();
};
