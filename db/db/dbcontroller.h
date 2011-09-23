#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <map>
#include <vector>
#include <string>

class FileOutputStream;
class FileInputStream;
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

        void initialize();

        FileOutputStream* open(char* ns, FILE_TYPE type);
        bool close(char* ns);

        void insert(char* ns, BSONObj* bson);
        std::vector<BSONObj*> find(char* ns, BSONObj* filter);
        BSONObj* findFirst(char* ns, BSONObj* filter);
        BSONObj* readBSON(FileInputStream* stream);
    protected:
    private:
        std::map<std::string, FileOutputStream*>  _spaces;

    private:
        long checkStructure(BSONObj* bson);
        void updateIndex(char* ns, BSONObj* bson, long filePos);
        void insertIndex(char* ns, BSONObj* bson, long filePos);
        void writeBSON(FileOutputStream* stream, BSONObj* obj);
};

#endif // DBCONTROLLER_H
