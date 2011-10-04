#include "bsoninputstream.h"
#include "inputstream.h"
#include "bson.h"

BSONInputStream::BSONInputStream(InputStream* is)
{
    _inputStream = is;
}

BSONInputStream::~BSONInputStream()
{
}

boost::shared_ptr<BSONObj> BSONInputStream::readBSON() const {
    boost::shared_ptr<BSONObj> obj(new BSONObj());
    int elements = _inputStream->readLong();
    for (int x = 0; x < elements; x++) {
        boost::shared_ptr<std::string> key = _inputStream->readString();

        int type = _inputStream->readLong();
        switch (type) {
            case BSON_TYPE:
                // Unsupported yet;
                break;
            case INT_TYPE:
                obj->add(*key, _inputStream->readInt());
                break;
            case LONG_TYPE:
                obj->add(*key, _inputStream->readLong());
                break;
            case DOUBLE_TYPE:
                obj->add(*key, _inputStream->readDoubleIEEE());
                break;
            case PTRCHAR_TYPE:
                obj->add(*key, _inputStream->readChars());
                break;
            case STRING_TYPE:
                obj->add(*key, _inputStream->readString().get());
                break;
        }
    }
    return obj;
}
