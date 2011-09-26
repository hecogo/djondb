#include <string>
#include <map>
#include <vector>

using namespace std;

class StreamException : public exception {
private:
    string *message;
public:

    StreamException(string *_message) {
        message = _message;
    }

    virtual const char* what() const throw () {
        return message->c_str();
    }
};


