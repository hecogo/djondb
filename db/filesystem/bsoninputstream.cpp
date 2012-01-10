#include "bsoninputstream.h"
#include "inputstream.h"
#include "bson.h"
#include "util.h"

#include <memory>

BSONInputStream::BSONInputStream(InputStream* is)
{
    _inputStream = is;
	 _log = getLogger(NULL);
}

BSONInputStream::~BSONInputStream()
{
	delete _log;
}

BSONObj* BSONInputStream::readBSON() const {
	Logger* log = getLogger(NULL);
    BSONObj* obj = new BSONObj();
    int elements = _inputStream->readLong();
	 if (log->isDebug()) log->debug("BSONInputStream::readBSON elements: %d", elements);
	 BSONInputStream* bis;
    for (int x = 0; x < elements; x++) {
        std::auto_ptr<string> key(_inputStream->readString());

	     if (log->isDebug()) log->debug("BSONInputStream::readBSON key: %s", key->c_str());
        int type = _inputStream->readLong();
        void* data = NULL;
		  BSONObj* inner;
        switch (type) {
            case BSON_TYPE:
					 inner = readBSON();
					 obj->add(*key.get(), *inner);
					 delete inner;
                break;
            case INT_TYPE:
                obj->add(*key.get(), _inputStream->readInt());
                break;
            case LONG_TYPE:
                obj->add(*key.get(), _inputStream->readLong());
                break;
            case DOUBLE_TYPE:
                obj->add(*key.get(), _inputStream->readDoubleIEEE());
                break;
            case PTRCHAR_TYPE:
                data = _inputStream->readChars();
                obj->add(*key.get(), (char*)data);
                free((char*)data);
                break;
            case STRING_TYPE:
                data = _inputStream->readString();
                obj->add(*key.get(), *(std::string*)data);
                delete (std::string*)data;
                break;
        }
    }
    return obj;
}

std::vector<BSONObj*> BSONInputStream::readBSONArray() const {
	if (_log->isDebug()) _log->debug(3, "BSONInputStream::readBSONArray");
	int elements = _inputStream->readLong();
	if (_log->isDebug()) _log->debug(3, "elements read: %d", elements);
	std::vector<BSONObj*> result;

	for (int x= 0; x < elements; x++) {
		BSONObj* obj = readBSON();
		if (_log->isDebug()) _log->debug(3, "obj: %s", obj->toChar());
		result.push_back(obj);
	}

	return result;
}
