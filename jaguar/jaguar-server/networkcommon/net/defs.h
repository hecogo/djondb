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


