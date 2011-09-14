#include "structure.h"
#include <string>

Structure::Structure()
{
    //ctor
}

Structure::~Structure()
{
    //dtor
}

void Structure::add(char* name)
{
    _elements.push_back(name);
    _id = 0;
}

long Structure::crc()
{
    if (_id == 0)
    {
        std::stringstream structure;

        for (std::vector<char*>::const_iterator i = _elements.begin(); i != _elements.end(); i++)
        {
            char* key = *i;
            structure << key << ";";
        }

        boost::crc_32_type crc;

        std::string s = structure.str();
        const char* buffer = s.c_str();
        crc.process_bytes(buffer, strlen(buffer));
        _id = crc.checksum();
    }
    return _id;
}
