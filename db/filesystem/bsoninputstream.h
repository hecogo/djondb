#ifndef BSONINPUTSTREAM_H
#define BSONINPUTSTREAM_H

class BSONObj;
class InputStream;

class BSONInputStream
{
    public:
        /** Default constructor */
        BSONInputStream(InputStream* is);
        /** Default destructor */
        virtual ~BSONInputStream();

        BSONObj* readBSON() const;

    protected:
    private:
        InputStream* _inputStream;
};

#endif // BSONINPUTSTREAM_H
