#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include <boost/crc.hpp>
#include <string>
#include <string.h>
#include <sstream>

using namespace std;

class Structure
{
    public:
        Structure();
        virtual ~Structure();
        void add(char* name);

        long crc();

    protected:
    private:
        long _id; // CRC Code
        vector<char*> _elements;
};


#endif // STRUCTURE_H
