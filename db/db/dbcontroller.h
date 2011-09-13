#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <map>
class FileOutputStream;
class BSONObj;

class DBController
{
    public:
        DBController();
        virtual ~DBController();

        FileOutputStream* open(char* ns);
        bool close(char* ns);

        void insert(char* ns, BSONObj* bson);
    protected:
    private:

        std::map<char*, FileOutputStream*>  _spaces;
};

#endif // DBCONTROLLER_H
