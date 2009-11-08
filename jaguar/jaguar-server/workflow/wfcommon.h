#include <exception>
#include <string>

using namespace std;

class WorkflowException : public exception {
private:
    char* message;
public:

    WorkflowException(char* _message) {
        message = _message;
    }

    virtual const char* what() const throw () {
        return message;
    }
};

