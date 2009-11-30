#include <exception>
#include <string>

using namespace std;

class WorkflowException : public exception {
private:
    const char* message;
public:

    WorkflowException(const char* _message) {
        message = _message;
    }

    virtual const char* what() const throw () {
        return message;
    }
};

