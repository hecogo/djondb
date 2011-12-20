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
               cout << "The type " << content->_type << " does not match the requested STRING for key2: " << key << endl; \
               throw "type does not match"; \
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
    BSON_TYPE,
    UNKNOWN_TYPE
//    PTR
};

class BSONContent {
    public:
        BSONContent() {}
        virtual ~BSONContent();

        BSONContent(const BSONContent& orig);
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
        void add(t_keytype, const BSONObj&);

        bool has(t_keytype);

        int* getInt(t_keytype) const;
        double* getDouble(t_keytype) const;
        long* getLong(t_keytype) const;
        char* getChars(t_keytype) const;
        std::string* getString(t_keytype) const;
        BSONObj* getBSON(t_keytype) const;
        void* get(t_keytype) const;

        BSONTYPE type(t_keytype) const;

        char* toChar() const;

        std::map<t_keytype, BSONContent* >::const_iterator begin() const;
        std::map<t_keytype, BSONContent* >::const_iterator end() const;
        int length() const;

    protected:
    private:
        std::map<t_keytype, BSONContent* > _elements;
};

#endif // BSONOBJ_H
