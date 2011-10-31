#ifndef BSONOBJ_H
#define BSONOBJ_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <string.h>

using namespace std;

typedef std::string t_keytype;

#define BSONCONTENT_FILL(kkey, ttype, vval) \
    BSONContent* content = new BSONContent(); \
    content->_type = ttype; \
    content->_element = vval; \
    _elements.insert(pair<t_keytype, BSONContent* >(kkey, content));

#define SEARCHBSON(key,ttype) \
    BSONContent* content; \
    for (std::map<t_keytype, BSONContent* >::const_iterator it = _elements.begin(); it != _elements.end(); it++) { \
        t_keytype itKey = it->first; \
        if (itKey.compare(key) == 0) { \
            content = it->second; \
            if (content->_type != ttype) { \
               throw "The type does not match"; \
            } \
            break; \
        } \
    }

enum BSONTYPE {
    INT_TYPE,
    DOUBLE_TYPE,
    LONG_TYPE,
    PTRCHAR_TYPE,
    STRING_TYPE,
    BSON_TYPE
//    PTR
};

class BSONContent {
    public:
        BSONContent() {}
        virtual ~BSONContent();

        BSONContent(const BSONContent& orig) {
            this->_type = orig._type;
            int len = 0;
            int* internalInt;
            long* internalLong;
            double* internalDouble;
            int i;
            long l;
            double d;
            switch (this->_type) {
                case STRING_TYPE:
                    this->_element = new std::string(*(std::string*)orig._element);
                    break;
                case PTRCHAR_TYPE:
                    len = strlen((char*)orig._element);
                    this->_element = malloc(len);
                    memcpy(this->_element, orig._element, len);
                    break;
                case INT_TYPE:
                    i = *((int*)orig._element);
                    internalInt = new int();
                    *internalInt = i;
                    this->_element = internalInt;
                    break;
                case LONG_TYPE:
                    l = *((long*)orig._element);
                    internalLong = new long();
                    *internalLong = l;
                    this->_element = internalLong;
                    break;
                case DOUBLE_TYPE:
                    d = *((double*)orig._element);
                    internalDouble = new double();
                    *internalDouble = d;
                    this->_element = internalDouble;
                    break;
                default:
                    break;
            }
        }

        void* _element;
        BSONTYPE _type;
};

class BSONObj
{
    public:
        BSONObj();
        BSONObj(const BSONObj& orig);
        virtual ~BSONObj();
//        void add(char*, void*);
        void add(t_keytype, int);
        void add(t_keytype, double);
        void add(t_keytype, long);
        void add(t_keytype, char*);
        void add(t_keytype, std::string);
        void add(t_keytype, BSONObj);

        bool has(t_keytype);

        int* getInt(t_keytype) const;
        double* getDouble(t_keytype) const;
        long* getLong(t_keytype) const;
        char* getChars(t_keytype) const;
        std::string* getString(t_keytype) const;
        BSONObj* getBSON(t_keytype) const;

        char* toChar() const;

        std::map<t_keytype, BSONContent* >::const_iterator begin() const;
        std::map<t_keytype, BSONContent* >::const_iterator end() const;
        int length() const;

    protected:
    private:
        std::map<t_keytype, BSONContent* > _elements;
};

#endif // BSONOBJ_H
