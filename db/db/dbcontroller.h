#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <map>
#include <vector>
#include <string>

class FileInputOutputStream;
class FileInputStream;
class BSONObj;
class Command;

enum FILE_TYPE {
    DATA_FTYPE,
    STRC_FTYPE,
    INDEX_FTYPE
};

typedef FileInputOutputStream StreamType;
struct Space {
    std::string ns;
    FILE_TYPE type;
    StreamType* stream;
};
typedef Space SpacesType;


class DBController
{
    public:
        DBController();
        virtual ~DBController();

        void initialize();
        void shutdown();

        bool close(char* ns);

        BSONObj* insert(char* ns, BSONObj* bson);
        void update(char* ns, BSONObj* bson);
        std::vector<BSONObj*> find(char* ns, const BSONObj& filter);
        BSONObj* findFirst(char* ns, BSONObj* filter);
        BSONObj* readBSON(StreamType* stream);
    protected:
    private:
        std::map<std::string, SpacesType>  _spaces;
        StreamType* open(std::string ns, FILE_TYPE type);

    private:
        long checkStructure(BSONObj* bson);
        void updateIndex(char* ns, BSONObj* bson, long filePos);
        void insertIndex(char* ns, BSONObj* bson, long filePos);
        void writeBSON(StreamType* stream, BSONObj* obj);
};

#endif // DBCONTROLLER_H
