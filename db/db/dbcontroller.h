#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <map>
class FileOutputStream;
class BSONObj;

enum FILE_TYPE {
    DATA_FTYPE,
    STRC_FTYPE,
    INDEX_FTYPE
};

class DBController
{
    public:
        DBController();
        virtual ~DBController();

        FileOutputStream* open(char* ns, FILE_TYPE type);
        bool close(char* ns);

        void insert(char* ns, BSONObj* bson);
    protected:
    private:
        std::map<char*, FileOutputStream*>  _spaces;

    private:
        long checkStructure(BSONObj* bson);
        void updateIndex()
};

#endif // DBCONTROLLER_H
