#ifndef BSONINPUTSTREAM_H
#define BSONINPUTSTREAM_H

#include <vector>

class BSONObj;
class BSONArrayObj;
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
        BSONObj* readBSON(const char* select) const;
		  std::vector<BSONObj*>* readBSONArray() const;
		  BSONArrayObj* readBSONInnerArray() const;

    protected:
	 private:
		  std::vector splitSelect(const char* select) const;
		  char* subselect(const char* select, const char* elment) const;
    private:
        InputStream* _inputStream;
		  Logger* _log;
};

#endif // BSONINPUTSTREAM_H
