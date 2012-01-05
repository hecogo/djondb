#ifndef BSONOUTPUTSTREAM_H
#define BSONOUTPUTSTREAM_H

#include <vector>

class BSONObj;
class OutputStream;

class BSONOutputStream
{
    public:
        /** Default constructor */
        BSONOutputStream(OutputStream* out);
        /** Default destructor */
        virtual ~BSONOutputStream();

        void writeBSON(const BSONObj& bson);
        void writeBSONArray(const std::vector<BSONObj*>& array);

    protected:
    private:
        OutputStream* _outputStream;
};

#endif // BSONOUTPUTSTREAM_H
