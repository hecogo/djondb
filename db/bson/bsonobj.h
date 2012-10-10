#ifndef BSONOBJ_H
#define BSONOBJ_H

#include "bsoncontent.h"
#include "bsondefs.h"
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <string.h>
#include "bsonarrayobj.h"

using namespace std;

class BSONObj
{
    public:
        BSONObj();
        BSONObj(const BSONObj& orig);
        virtual ~BSONObj();
//        void add(char*, void*);
        void add(t_keytype, int);
        void add(t_keytype, double);
        void add(t_keytype, long int);
        void add(t_keytype, long long);
        void add(t_keytype, std::string);
        void add(t_keytype, const BSONObj&);
        void add(t_keytype, const BSONArrayObj&);

        bool has(t_keytype) const;

        int* getInt(t_keytype) const;
        double* getDouble(t_keytype) const;
        long int* getLong(t_keytype) const;
        long long* getLong64(t_keytype) const;
        std::string getString(t_keytype) const;
        BSONObj* getBSON(t_keytype) const;
        BSONArrayObj* getBSONArray(t_keytype) const;
        void* get(t_keytype) const;
        BSONContent* getContent(t_keytype) const;
        BSONContent* getContent(t_keytype, BSONTYPE) const;

		  BSONContent getXpath(const std::string& xpath) const;

		  BSONObj* select(const char* sel) const;

        BSONTYPE type(t_keytype) const;

        char* toChar() const;

		  typedef std::map<t_keytype, BSONContent* >::iterator iterator;
		  typedef std::map<t_keytype, BSONContent* >::const_iterator const_iterator;

        const_iterator begin() const;
        const_iterator end() const;
        int length() const;

		  bool operator ==(const BSONObj& obj) const;
		  bool operator !=(const BSONObj& obj) const;

    protected:
	 private:
		  void fillContent(t_keytype kkey, BSONTYPE ttype, void* vval);
	 private:
		  std::map<t_keytype, BSONContent* > _elements;
};

#endif // BSONOBJ_H
