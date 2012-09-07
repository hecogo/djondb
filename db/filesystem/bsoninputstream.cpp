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
#include "memorystream.h"

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
	return readBSON("*");
}

BSONObj* BSONInputStream::readBSON(const char* select) const {
	Logger* log = getLogger(NULL);
	BSONObj* obj = new BSONObj();
	int elements = _inputStream->readLong();
	if (log->isDebug()) log->debug("BSONInputStream::readBSON elements: %d", elements);
	BSONInputStream* bis;
	for (int x = 0; x < elements; x++) {
		std::auto_ptr<string> key(_inputStream->readString());

		int type = _inputStream->readLong();
		void* data = NULL;
		BSONObj* inner;
		switch (type) {
			case BSON_TYPE: {
									 inner = readBSON();
#ifdef DEBUG
									 if (log->isDebug()) log->debug("BSONInputStream::readBSON key: %s, (BSONObj)", key->c_str());
#endif
									 obj->add(*key.get(), *inner);
									 delete inner;
									 break;
								 }
			case INT_TYPE: {
									int i = _inputStream->readInt();
									obj->add(*key.get(), i);
#ifdef DEBUG
									if (log->isDebug()) log->debug("BSONInputStream::readBSON key: %s, value: %d", key->c_str(), i);
#endif
									break;
								}
			case LONG_TYPE: {
									 long l = _inputStream->readLong();
#ifdef DEBUG
									 if (log->isDebug()) log->debug("BSONInputStream::readBSON key: %s, value: %d", key->c_str(), l);
#endif
									 obj->add(*key.get(), l);
									 break;
								 }
			case DOUBLE_TYPE: {
										double d = _inputStream->readDoubleIEEE();
#ifdef DEBUG
										if (log->isDebug()) log->debug("BSONInputStream::readBSON key: %s, value: %d", key->c_str(), d);
#endif
										obj->add(*key.get(), d);
										break;
									}
			case PTRCHAR_TYPE: {
										 data = _inputStream->readChars();
#ifdef DEBUG
										 if (log->isDebug()) log->debug("BSONInputStream::readBSON key: %s, value: %s", key->c_str(), data);
#endif
										 obj->add(*key.get(), (char*)data);
										 free((char*)data);
										 break;
									 }
			case STRING_TYPE: {
										data = _inputStream->readString();
#ifdef DEBUG
										if (log->isDebug()) log->debug("BSONInputStream::readBSON key: %s, value: %s", key->c_str(), ((std::string*)data)->c_str());
#endif
										obj->add(*key.get(), *(std::string*)data);
										delete (std::string*)data;
										break;
									}
			case BSONARRAY_TYPE:
									{
										BSONArrayObj* array = readBSONInnerArray();
#ifdef DEBUG
										if (log->isDebug()) log->debug("BSONInputStream::readBSON key: %s, (BSONArray)", key->c_str());
#endif
										obj->add(*key.get(), *array);
										delete array;
										break;
									}
		}
	}
	delete log;
	return obj;
}

BSONArrayObj* BSONInputStream::readBSONInnerArray() const {
#ifdef DEBUG
	if (_log->isDebug()) _log->debug(3, "BSONInputStream::readBSONInnerArray");
#endif
	int elements = _inputStream->readLong();
#ifdef DEBUG
	if (_log->isDebug()) _log->debug(3, "elements read: %d", elements);
#endif
	BSONArrayObj* result = new BSONArrayObj();

	for (int x= 0; x < elements; x++) {
		BSONObj* obj = readBSON();
#ifdef DEBUG
		if (_log->isDebug()) _log->debug(3, "obj: %s", obj->toChar());
#endif
		result->add(*obj);
		delete obj;
	}

	return result;
}

std::vector<BSONObj*>* BSONInputStream::readBSONArray() const {
#ifdef DEBUG
	if (_log->isDebug()) _log->debug(3, "BSONInputStream::readBSONArray");
#endif
	int elements = _inputStream->readLong();
#ifdef DEBUG
	if (_log->isDebug()) _log->debug(3, "elements read: %d", elements);
#endif
	std::vector<BSONObj*>* result = new std::vector<BSONObj*>();

	for (int x= 0; x < elements; x++) {
		BSONObj* obj = readBSON();
#ifdef DEBUG
		if (_log->isDebug()) _log->debug(3, "obj: %s", obj->toChar());
#endif
		result->push_back(obj);
	}

	return result;
}

std::vector bsoninputstream::splitSelect(const char* select) const {
	std::vector<std::string> elements = split(std::string(select), ",");

	return elements;
}

char* bsoninputstream::subselect(const char* select, const char* name) const {
	std::vector<std::string> elements = splitSelect(select);
	MemoryStream ms(2048);

	char* startXpath = format("%s.", name);
	int lenStartXpath = strlen(startXpath);
	bool first = true;
	for (std::vector<std::string>::const_iterator i = elements.begin(); i != elements.end(); i++) {
		std::string element = *i;
		if (startsWith(element, "$")) {
			// Remvoes the $" " from the element
			element = strcpy(element.c_str(), 2, element.length() - 3);
			if (startsWith(element.c_str(), startXpath)) {
				 char* suffix = strcpy(element, lenStartXpath, strlen(element) - lenStartXpath);
				 ms.writeChars(suffix);
				 if (!first) {
					 ms.writeChars(", ");
				 }
				 first = false;
				 free(suffix);
			}
		}
	}
}
