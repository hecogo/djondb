#ifndef BSONINPUTSTREAM_H
#define BSONINPUTSTREAM_H

#include <set>
#include <vector>
#include <string>

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
		  std::vector<BSONObj*>* readBSONArray(const char* select) const;
		  BSONArrayObj* readBSONInnerArray() const;
		  BSONArrayObj* readBSONInnerArray(const char* select) const;

    protected:
	 private:
		  std::set<std::string> splitSelect(const char* select) const;
		  char* subselect(const char* select, const char* elment) const;
    private:
        InputStream* _inputStream;
		  Logger* _log;
};

#endif // BSONINPUTSTREAM_H
