#ifndef BSONINPUTSTREAM_H
#define BSONINPUTSTREAM_H

#include <vector>

class BSONObj;
class InputStream;
class Logger;

class BSONInputStream
{
    public:
        /** Default constructor */
        BSONInputStream(InputStream* is);
        /** Default destructor */
        virtual ~BSONInputStream();

        BSONObj* readBSON() const;
		  std::vector<BSONObj*> readBSONArray() const;

    protected:
    private:
        InputStream* _inputStream;
		  Logger* _log;
};

#endif // BSONINPUTSTREAM_H
