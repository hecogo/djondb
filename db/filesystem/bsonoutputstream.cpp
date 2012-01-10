#include "bsonoutputstream.h"

#include "outputstream.h"
#include "bson.h"
#include "util.h"
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
	Logger* log = getLogger(NULL);
	if (log->isDebug()) log->debug("BSONOutputStream::writeBSON bson elements: %d", bson.length());
    _outputStream->writeLong(bson.length());
    for (std::map<t_keytype, BSONContent* >::const_iterator i = bson.begin(); i != bson.end(); i++) {
        t_keytype key = i->first;
		  if (log->isDebug()) log->debug("BSONOutputStream::writeBSON name: %s", key.c_str());
        _outputStream->writeString(key);
        BSONContent* cont = i->second;
        _outputStream->writeLong(cont->type());
        char* text;
		  BSONObj* inner;
        switch (cont->type()) {
            case BSON_TYPE:
                inner = (BSONObj*)cont->_element;
					 writeBSON(*inner); 
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
                _outputStream->writeString(*str);
                break;
        }
    }
	 delete log;
}

void BSONOutputStream::writeBSONArray(const std::vector<BSONObj*>& array) {
	Logger* log = getLogger(NULL);
	if (log->isDebug()) log->debug("BSONOutputStream::writeBSONArray elements: %d", array.size());
	_outputStream->writeLong(array.size());
	for (std::vector<BSONObj*>::const_iterator i = array.begin(); i != array.end(); i++) {
		BSONObj* obj = *i;
		writeBSON(*obj);
	}
	delete log;
}
