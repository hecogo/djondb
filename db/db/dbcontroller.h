#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <map>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

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

        void insert(char* ns, boost::shared_ptr<BSONObj> bson);
        std::vector<boost::shared_ptr<BSONObj> > find(char* ns, boost::shared_ptr<BSONObj> filter);
        boost::shared_ptr<BSONObj> findFirst(char* ns, boost::shared_ptr<BSONObj> filter);
        boost::shared_ptr<BSONObj> readBSON(StreamType* stream);
    protected:
    private:
        std::map<std::string, SpacesType>  _spaces;
        StreamType* open(std::string ns, FILE_TYPE type);

    private:
        long checkStructure(boost::shared_ptr<BSONObj> bson);
        void updateIndex(char* ns, boost::shared_ptr<BSONObj> bson, long filePos);
        void insertIndex(char* ns, boost::shared_ptr<BSONObj> bson, long filePos);
        void writeBSON(StreamType* stream, boost::shared_ptr<BSONObj> obj);
};

#endif // DBCONTROLLER_H
