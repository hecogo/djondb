#include "bsoninputstream.h"
#include "inputstream.h"
#include "bson.h"

#include <memory>

BSONInputStream::BSONInputStream(InputStream* is)
{
    _inputStream = is;
}

BSONInputStream::~BSONInputStream()
{
}

BSONObj* BSONInputStream::readBSON() const {
    BSONObj* obj = new BSONObj();
    int elements = _inputStream->readLong();
    for (int x = 0; x < elements; x++) {
        std::auto_ptr<string> key(_inputStream->readString());

        int type = _inputStream->readLong();
        switch (type) {
            case BSON_TYPE:
                // Unsupported yet;
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
                obj->add(*key.get(), _inputStream->readChars());
                break;
            case STRING_TYPE:
                obj->add(*key.get(), _inputStream->readString());
                break;
        }
    }
    return obj;
}
