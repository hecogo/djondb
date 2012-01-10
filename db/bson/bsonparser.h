#ifndef BSONPARSER_H
#define BSONPARSER_H

#include <string>

class BSONObj;

class BSONParser
{
    public:
        /** Default constructor */
        BSONParser();
        /** Default destructor */
        virtual ~BSONParser();

        static BSONObj* parse(char* sbson);

    protected:
    private:
};

#endif // BSONPARSER_H
