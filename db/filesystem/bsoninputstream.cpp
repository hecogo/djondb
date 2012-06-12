// *********************************************************************************************************************
// file:
// author: Juan Pablo Crossley (crossleyjuan@gmail.com)
// created:
// updated:
// license:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// *********************************************************************************************************************

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
	 delete log;
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
