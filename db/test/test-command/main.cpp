#include <iostream>
#include "bson.h"
#include "fileinputstream.h"
#include "fileoutputstream.h"
#include "bsonoutputstream.h"
#include "command.h"
#include <assert.h>

#include <string>

using namespace std;

int main()
{
    CommandParser* parser = new CommandParser();
    FileOutputStream* fos = new FileOutputStream("TestParse.dat", "wb+");
    fos->writeInt(1); // Insert
    fos->writeString(new std::string("bustomer"));
    BSONObj* obj = new BSONObj();
    obj->add("name", new std::string("Peter"));
    BSONOutputStream* bsonOut = new BSONOutputStream(fos);
    bsonOut->writeBSON(*obj);
    fos->close();

    FileInputStream* fis = new FileInputStream("TestParse.dat", "rb");
    Command* cmd = parser->parse(fis);

    assert(cmd->commandType() == INSERT);
    InsertCommand* insCmd = (InsertCommand*)cmd;
    assert(insCmd->nameSpace() != NULL);
    assert(insCmd->nameSpace()->compare("bustomer") == 0);
    BSONObj* bson = insCmd->bson();
    assert(bson != NULL);
    std::string* name = bson->getString("name");
    assert(name != NULL);
    assert(name->compare("Peter") == 0);
    return 0;
}
