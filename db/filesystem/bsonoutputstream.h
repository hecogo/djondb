#ifndef BSONOUTPUTSTREAM_H
#define BSONOUTPUTSTREAM_H

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

    protected:
    private:
        OutputStream* _outputStream;
};

#endif // BSONOUTPUTSTREAM_H
