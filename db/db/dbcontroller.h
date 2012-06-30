#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <map>
#include <vector>
#include <string>

class FileInputOutputStream;
class FileInputStream;
class BSONObj;
class Command;
class Logger;

enum FILE_TYPE {
    DATA_FTYPE,
    STRC_FTYPE,
    INDEX_FTYPE
};

typedef FileInputOutputStream StreamType;
struct Space {
    std::string ns;
	 std::map<FILE_TYPE, StreamType*>* streams;
};
typedef Space SpacesType;


class DBController
{
    public:
        DBController();
        virtual ~DBController();

        void initialize();
        void initialize(std::string dataDir);
        void shutdown();

        bool close(char* db, char* ns);

        BSONObj* insert(char* db, char* ns, BSONObj* bson);
		  bool dropNamespace(char* db, char* ns);
        void update(char* db, char* ns, BSONObj* bson);
        std::vector<BSONObj*>* find(char* db, char* ns, const BSONObj& filter);
        std::vector<BSONObj*>* find(char* db, char* ns, const char* filter);
        BSONObj* findFirst(char* db, char* ns, BSONObj* filter);
        BSONObj* findFirst(char* db, char* ns, const char* filter);
        BSONObj* readBSON(StreamType* stream);
		  std::vector<std::string>* dbs() const;
		  std::vector<std::string>* namespaces(const char* db) const;

    protected:
    private:
		  std::map<std::string, std::map<std::string, SpacesType>* > _spaces;
        StreamType* open(std::string db, std::string ns, FILE_TYPE type);
		  std::vector<BSONObj*>* findFullScan(char* db, char* ns, const BSONObj& filter);
		  std::vector<BSONObj*>* findFullScan(char* db, char* ns, const char* filter);
		  Logger* _logger;
		  std::string fileName(std::string ns, FILE_TYPE type) const;

		  std::string _dataDir;
		  bool _initialized;

    private:
		  void saveDatabases();
		  void clearCache();
        long checkStructure(BSONObj* bson);
        void updateIndex(char* db, char* ns, BSONObj* bson, long filePos);
        void insertIndex(char* db, char* ns, BSONObj* bson, long filePos);
        void writeBSON(StreamType* stream, BSONObj* obj);
};

#endif // DBCONTROLLER_H
