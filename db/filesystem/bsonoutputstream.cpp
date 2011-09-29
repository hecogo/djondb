#include "bsonoutputstream.h"

#include "outputstream.h"
#include "bson.h"
#include <string.h>

BSONOutputStream::BSONOutputStream(OutputStream* out)
{
    _outputStream = out;
    //ctor
}

BSONOutputStream::~BSONOutputStream()
{
    //dtor
}


void BSONOutputStream::writeBSON(const BSONObj& bson) {
    _outputStream->writeLong(bson.length());
    for (std::map<t_keytype, BSONContent*>::const_iterator i = bson.begin(); i != bson.end(); i++) {
        t_keytype key = i->first;
        _outputStream->writeString(&key);
        BSONContent* cont = i->second;
        _outputStream->writeLong(cont->_type);
        char* text;
        switch (cont->_type) {
            case BSON_TYPE:
                // Unsupported yet;
                break;
            case INT_TYPE:
                _outputStream->writeInt(*((int*)cont->_element));
                break;
            case LONG_TYPE:
                _outputStream->writeLong(*((long*)cont->_element));
                break;
            case DOUBLE_TYPE:
                _outputStream->writeDoubleIEEE(*((double*)cont->_element));
                break;
            case PTRCHAR_TYPE:
                text = (char*)cont->_element;
                _outputStream->writeChars(text, strlen(text));
                break;
            case STRING_TYPE:
                string* str = (string*)cont->_element;
                _outputStream->writeString(str);
                break;
        }
    }
}

