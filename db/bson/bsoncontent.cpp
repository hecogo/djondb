#include "bsoncontent.h"
#include "bsonobj.h"
#include "util.h"
#include <stdlib.h>

using namespace std;

BSONContent::~BSONContent() {
	if (!_element) {
		return;
	}
	switch (_type) {
		case STRING_TYPE:
			delete ((string*)_element);
			break;
		case PTRCHAR_TYPE:
			free (_element);
			break;
		case INT_TYPE:
			delete ((int*)_element);
			break;
		case LONG_TYPE:
			delete ((long*)_element);
			break;
		case DOUBLE_TYPE:
			delete ((double*)_element);
			break;
		case BSON_TYPE:
			delete ((BSONObj*)_element);
			break;
		default:
			break;
	}
	_element = 0;
}

BSONContent::BSONContent(const BSONContent& orig) {
	this->_type = orig._type;
	int len = 0;
	int* internalInt;
	long* internalLong;
	double* internalDouble;
	int i;
	long l;
	double d;
	BSONObj* bson;
	BSONObj* internalBson;
	switch (this->_type) {
		case STRING_TYPE:
			this->_element = new std::string(*(std::string*)orig._element);
			break;
		case PTRCHAR_TYPE:
			len = strlen((char*)orig._element);
			this->_element = malloc(len+1);
			memset(this->_element, 0, len + 1);
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
		case BSON_TYPE:
			bson = (BSONObj*)orig._element;
			internalBson = new BSONObj(*bson);
			this->_element = internalBson;
			break;
		default:
			break;
	}
}


bool BSONContent::operator ==(const BSONContent& content) {
	Logger* log = getLogger(NULL);

	if (log->isDebug()) log->debug("operator == ");

	if (this->_type != content._type) {
		return false;
	} else {
		void* cont1 = this->_element;
		void* cont2 = content._element;
		// if the pointers are equal it's pointless to compare the contents
		if (cont1 == cont2) {
			return true;
		} else {
			bool result;
			switch (this->_type) {
				case STRING_TYPE:
					result = ((std::string*)cont1)->compare(*(std::string*)cont2) == 0;
					break;
				case PTRCHAR_TYPE: 
					{
						char* c1 = (char*)cont1;
						char* c2 = (char*)cont2;
						result = strcmp(c1, c2) == 0;
					}
					break;
				case INT_TYPE: 
					{
						int i1 = *(int*)cont1;
						int i2 = *(int*)cont2;
						result = (i1 == i2);
					}
					break;
				case LONG_TYPE:
					{
						long l1 = *(long*)cont1;
						long l2 = *(long*)cont2;
						result = (l1 == l2);
					}
					break;
				case DOUBLE_TYPE:
					{
						long l1 = *(long*)cont1;
						long l2 = *(long*)cont2;
						result = (l1 == l2);
					}
					break;
				case BSON_TYPE:
					return false;
					break;
				default:
					break;
			}
			return result;
		}	
	}
}
