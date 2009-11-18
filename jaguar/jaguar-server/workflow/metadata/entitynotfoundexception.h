#ifndef ENTITYNOTFOUNDEXCEPTION_H_INCLUDED
#define ENTITYNOTFOUNDEXCEPTION_H_INCLUDED

class EntityNotFoundException : public exception  {
private:
    string* message;
public:
    EntityNotFoundException(string *_message);
    virtual const char* what() const throw ();
};


#endif // ENTITYNOTFOUNDEXCEPTION_H_INCLUDED
