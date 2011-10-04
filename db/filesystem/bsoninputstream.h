#ifndef BSONINPUTSTREAM_H
#define BSONINPUTSTREAM_H

class BSONObj;
class InputStream;

#include <boost/shared_ptr.hpp>

class BSONInputStream
{
    public:
        /** Default constructor */
        BSONInputStream(InputStream* is);
        /** Default destructor */
        virtual ~BSONInputStream();

        boost::shared_ptr<BSONObj> readBSON() const;

    protected:
    private:
        InputStream* _inputStream;
};

#endif // BSONINPUTSTREAM_H
