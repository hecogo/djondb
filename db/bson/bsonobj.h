#ifndef BSONOBJ_H
#define BSONOBJ_H

#include <map>
#include <string>

using namespace std;

#define BSONCONTENT_FILL(kkey, ttype, vval) \
    BSONContent* content = new BSONContent(); \
    content->_type = ttype; \
    content->_element = vval; \
    _elements.insert(pair<char*, BSONContent* >(kkey, content));

enum BSONTYPE {
    INT,
    DOUBLE,
    LONG,
    PTRCHAR,
    STRING,
    BSON
//    PTR
};

class BSONContent {
    public:
        BSONContent() {}
        virtual ~BSONContent();

        BSONContent(const BSONContent& content) {
            this->_element = content._element;
            this->_type = content._type;
        }

        void* _element;
        BSONTYPE _type;
};

class BSONObj
{
    public:
        BSONObj();
        virtual ~BSONObj();
//        void add(char*, void*);
        void add(char*, int);
        void add(char*, double);
        void add(char*, long);
        void add(char*, char*);
        void add(char*, std::string);
        void add(char*, BSONObj*);

        char* toChar() const;
    protected:
    private:
        std::map<char*, BSONContent* > _elements;
};

#endif // BSONOBJ_H
