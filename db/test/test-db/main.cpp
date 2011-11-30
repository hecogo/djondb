#include <iostream>
#include <dbcontroller.h>
#include <util.h>
#include <defs.h>
#include <ctime>
#ifndef WINDOWS
#include <time.h>
#endif
#ifdef WINDOWS
#include <Windows.h>
#endif
#include "bson.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "fileoutputstream.h"
#include "fileinputstream.h"
#include "bplusindex.cpp"
#include "math.h"

using namespace std;

DBController controller;

std::vector<std::string*> __ids;

int testInsert(BSONObj* o) {
    BSONObj* res = controller.insert("sp1.customer", o);
    delete res;
}

int testInsertWithStringId() {
    cout << "testInsertWithStringId" << endl;
    BSONObj obj;
    std::string* id = uuid();
    obj.add("_id", *id);
    obj.add("name", "cross");
    delete id;
    BSONObj* res = controller.insert("sp1.customer", &obj);
    if (res != NULL) {
        delete res;
    }
}

int testInsertWithCharId() {
    cout << "testInsertWithCharId" << endl;
    BSONObj obj;
    std::string* id = uuid();
    obj.add("_id", id->c_str());
    obj.add("name", "cross");
    delete id;
    BSONObj* res = controller.insert("sp1.customer", &obj);
    if (res != NULL) {
        delete res;
    }
}

int testInsertWithoutId() {
    cout << "testInsertWithoutId" << endl;
    BSONObj obj;
    obj.add("name", "cross");
    BSONObj* res = controller.insert("sp1.customer", &obj);
    assert(res != NULL);
    assert(res->has("_id"));
    delete res;
}
int testMassiveInsert(int inserts) {
    std::auto_ptr<Logger> log(getLogger(NULL));

    log->startTimeRecord();

    FileOutputStream fos("temp.txt", "wb+");

    for (int x = 0; x < inserts; x++) {
        BSONObj* obj = new BSONObj();
        obj->add("name", "John");
        char temp[700];
        memset(temp, 0, 699);
        memset(temp, 'a', 700);
        obj->add("content", std::string(temp));
        obj->add("last", std::string("Smith"));
        testInsert(obj);

        int test = rand() % 10;
        if (test > 0) {
            __ids.push_back(new std::string(((std::string*)obj->getString("_id"))->c_str()));
            fos.writeString(obj->getString("_id"));
        }
        if ((x % 1000000) == 0) {

            cout<< "inserts " << x << endl;
        }
        delete obj;
    }
    fos.close();

    log->stopTimeRecord();

    int secs = log->recordedTime().totalSecs();

    cout<< "inserts " << inserts << ", secs: " << secs << endl;

    if (secs > 0) {
        cout << "Throughput: " << (inserts / secs) << " ops." << endl;
        cout << "------------------------------------------------------------" << endl;
    }
}

void testFinds() {


    std::auto_ptr<Logger> log(getLogger(NULL));

    log->startTimeRecord();

    for (std::vector<string*>::iterator i = __ids.begin(); i != __ids.end(); i++) {
        string* id = *i;

        BSONObj obj;
        obj.add("_id", *id);
        BSONObj* res = controller.findFirst("sp1.customer", &obj);
        std::string* id2 = res->getString("_id");
//        cout << "Looking for: " << *id << endl;
//        cout << "Found        " << *id2 << endl;
        if ((id2 == NULL) || (id2->compare(*id) != 0)) {
            if (id2 != NULL) {
                cout << "Looking for: " << *id << " and got " << *id2 << endl;
            }
            cout << "Error " << endl;
        }
        delete res;
    }

    log->stopTimeRecord();

    int secs = log->recordedTime().totalSecs();

    cout<< "finds " << __ids.size() << ", secs: " << secs << endl;

    if (secs > 0) {
        cout << "Throughput: " << (__ids.size() / secs) << " ops." << endl;
        cout << "------------------------------------------------------------" << endl;
    }
}

void testFindPrevious() {

    std::auto_ptr<Logger> log(getLogger(NULL));

    FileInputStream fis("temp.txt", "rb");
    std::vector<std::string*> ids;
    while (!fis.eof()) {
        ids.push_back(fis.readString());
    }
    fis.close();

    log->startTimeRecord();

    for (std::vector<string*>::iterator i = ids.begin(); i != ids.end(); i++) {
        string* id = *i;

        BSONObj obj;
        obj.add("_id", *id);
        BSONObj* res = controller.findFirst("sp1.customer", &obj);
        if (res == NULL) {
            cout << "Looking for " << *id << " does not returned any match" << endl;
        } else {
            std::string* id2 = res->getString("_id");
    //        cout << "Looking for: " << *id << endl;
    //        cout << "Found        " << *id2 << endl;
            if ((id2 == NULL) || (id2->compare(*id) != 0)) {
                if (id2 != NULL) {
                    cout << "Looking for: " << *id << " and got " << *id2 << endl;
                }
                cout << "Error " << endl;
            }
            delete res;
        }
    }

    log->stopTimeRecord();

    int secs = log->recordedTime().totalSecs();

    cout<< "finds " << ids.size() << ", secs: " << secs << endl;

    if (secs > 0) {
        cout << "Throughput: " << (ids.size() / secs) << " ops." << endl;
        cout << "------------------------------------------------------------" << endl;
    }
}

void testIndex(std::vector<std::string> ids) {
    std::auto_ptr<BPlusIndex> tree(new BPlusIndex());

    std::auto_ptr<Logger> log(getLogger(NULL));

    cout << "Staring index insert test" << endl;
    log->startTimeRecord();
    // Inserting
    int x = 0;
    for (std::vector<std::string>::iterator i = ids.begin(); i != ids.end(); i++) {
        BSONObj id;
        id.add("_id", *i);
        tree->add(id, 0);
        x++;
    }
    log->stopTimeRecord();
    DTime time = log->recordedTime();
    cout << "Inserted " << x << " keys in " << time.toChar() << endl;

    cout << "Staring index search test" << endl;
    log->startTimeRecord();
    while (ids.size() > 0) {
        int pos = rand() % ids.size();
        while (pos > ids.size()) {
            pos = rand() % ids.size();
        }
        std::vector<std::string>::iterator i = ids.begin() + pos;
        std::string guid = *i;

        BSONObj id;
        id.add("_id", guid);
        Index* index = tree->find(id);
        assert(index != NULL);
        BSONObj* key = index->key;
        assert(key != NULL);
        assert(key->getString("_id") != NULL);
        assert(key->getString("_id")->compare(guid) == 0);

        ids.erase(i);
    }
    log->stopTimeRecord();
    time = log->recordedTime();
    cout << "Searched " << x << " keys in " << time.toChar() << endl;

}

void testSimpleIndex() {
    FileInputStream fis("simple.dat", "rb");
    std::vector<std::string> ids;
    while (!fis.eof()) {
        std::string* s = fis.readString();
        ids.push_back(*s);
        delete s;
    }
    fis.close();
    testIndex(ids);
}

void testComplexIndex() {
    FileInputStream fis("guids.txt", "rb");
    std::vector<std::string> ids;
    while (!fis.eof()) {
        std::string* s= fis.readString();
        ids.push_back(*s);
        delete s;
    }
    fis.close();
    testIndex(ids);
}

int main(int argc, char* args[])
{
    if (argc < 2) {
        cout << "Usage: " << endl;
        cout << "    test-db inserts" << endl << endl;
        cout << "inserts:   number of inserts to execute" << endl << endl;
        return 0;
    }

    FileOutputStream fos("simple.dat", "wb");
    fos.writeString(&std::string("1"));
    fos.writeString(&std::string("4"));
    fos.writeString(&std::string("11"));
    fos.writeString(&std::string("6"));
    fos.writeString(&std::string("15"));
    fos.writeString(&std::string("20"));
    fos.writeString(&std::string("18"));
    fos.writeString(&std::string("8"));
    fos.writeString(&std::string("19"));
    fos.writeString(&std::string("7"));
    fos.writeString(&std::string("13"));
    fos.writeString(&std::string("9"));
    fos.writeString(&std::string("14"));
    fos.writeString(&std::string("5"));
    fos.writeString(&std::string("17"));
    fos.writeString(&std::string("10"));
    fos.writeString(&std::string("12"));
    fos.writeString(&std::string("16"));
    fos.writeString(&std::string("12"));
    fos.writeString(&std::string("13"));
    fos.close();

    testInsertWithStringId();
    testInsertWithCharId();
    testInsertWithoutId();
    testSimpleIndex();
    testComplexIndex();
    controller.initialize();

    testFindPrevious();
    int x = atoi(args[1]);
    testMassiveInsert(x);
    testFinds();

    controller.shutdown();
    return 0;
}
