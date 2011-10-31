#include <iostream>
#include <fileinputstream.h>
#include <fileoutputstream.h>
#include "bsonoutputstream.h"
#include "bsoninputstream.h"
#include "bsonobj.h"
#include <string.h>
#include <assert.h>
#include <memory>

using namespace std;

int testFileOutputStream() {
    FileOutputStream stream("test.txt", "wb");
    stream.writeChars("Hello World!", 12);
    stream.close();
    return 0;
}

int testFileInputStream() {
    FileInputStream stream("test.txt", "rb");
    char* text = stream.readChars();

    assert(strcmp(text, "Hello World!") == 0);
    stream.close();
    return 0;
}

void testBSONStreams() {
    cout << "testBSONStreams" << endl;
    std::auto_ptr<FileOutputStream> fos(new FileOutputStream("bson.txt", "wb"));
    std::auto_ptr<BSONOutputStream> bsonOut(new BSONOutputStream(fos.get()));

    std::auto_ptr<BSONObj> obj(new BSONObj());
    // Add in
    obj->add("int", 1);
    obj->add("string", std::string("test"));
    obj->add("char*", (char*)"char*");
    obj->add("long", 1L);
    obj->add("double", 1.1);

    bsonOut->writeBSON(*obj);

    fos->close();

    obj.release();

    std::auto_ptr<FileInputStream> fis(new FileInputStream("bson.txt", "rb"));
    std::auto_ptr<BSONInputStream> bsonIn(new BSONInputStream(fis.get()));

    obj = std::auto_ptr<BSONObj>(bsonIn->readBSON());

    assert(obj->getInt("int") != NULL);
    assert(*obj->getInt("int") == 1);

    assert(obj->getString("string") != NULL);
    assert(((std::string*)obj->getString("string"))->compare("test") == 0);

    assert(obj->getChars("char*") != NULL);
    assert(strcmp((char*) obj->getChars("char*"), "char*") == 0);

    assert(obj->getLong("long") != NULL);
    assert(*obj->getLong("long") == 1L);

    assert(obj->getDouble("double") != NULL);
    assert(*obj->getDouble("double") == 1.1);

    fis->close();
}

int main()
{
    testFileOutputStream();
    testFileInputStream();
    testBSONStreams();
    return 0;
}
