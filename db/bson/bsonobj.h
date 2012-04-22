#ifndef BSONOBJ_H
#define BSONOBJ_H

#include "bsoncontent.h"
#include "defs.h"
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <string.h>
#include "bsonarrayobj.h"

using namespace std;

#define BSONCONTENT_FILL(kkey, ttype, vval) \
    BSONContent* content = new BSONContent(); \
    content->setType(ttype); \
    content->_element = vval; \
    _elements.insert(pair<t_keytype, BSONContent* >(kkey, content));



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
        void add(t_keytype, const BSONArrayObj&);

        bool has(t_keytype) const;

        int* getInt(t_keytype) const;
        double* getDouble(t_keytype) const;
        long* getLong(t_keytype) const;
        char* getChars(t_keytype) const;
        std::string* getString(t_keytype) const;
        BSONObj* getBSON(t_keytype) const;
        BSONArrayObj* getBSONArray(t_keytype) const;
        void* get(t_keytype) const;
        BSONContent* getContent(t_keytype) const;
        BSONContent* getContent(t_keytype, BSONTYPE) const;

		  BSONContent getXpath(const std::string& xpath) const;

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
