#ifndef BSON_DEFS_H_INCLUDED
#define BSON_DEFS_H_INCLUDED

#include <string>

typedef std::string t_keytype;


enum BSONTYPE {
    INT_TYPE,
    DOUBLE_TYPE,
    LONG_TYPE,
    PTRCHAR_TYPE,
    STRING_TYPE,
    BSON_TYPE,
	 BSONARRAY_TYPE,
    UNKNOWN_TYPE
//    PTR
};

#endif //BSON_DEFS_H_INCLUDED
