#include <iostream>
#include <dbcontroller.h>
#include <util.h>
#include <config.h>
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

using namespace std;

DBController controller;

std::vector<std::string*> __ids;

int testInsert(BSONObj* o) {
    controller.insert("sp1.customer", o);
}

int testMassiveInsert(int inserts) {
    std::auto_ptr<Logger> log(getLogger(NULL));

    log->startTimeRecord();

    FileOutputStream fos("temp.txt", "wb+");

    for (int x = 0; x < inserts; x++) {
        BSONObj* obj = new BSONObj();
        obj->add("name", new std::string("John"));
        char temp[700];
        memset(temp, 0, 699);
        memset(temp, 'a', 700);
        obj->add("content", new std::string(temp));
        obj->add("last", new std::string("Smith"));
        testInsert(obj);

        int test = rand() % 10;
        if (test > 0) {
            __ids.push_back(new std::string(((std::string*)obj->getString("_id"))->c_str()));
            fos.writeString(obj->getString("_id"));
        }
        if ((x % 1000000) == 0) {

            cout<< "inserts " << x << endl;
        }
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

        BSONObj* obj = new BSONObj();
        obj->add("_id", id);
        BSONObj* res = controller.findFirst("sp1.customer", obj);
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
        delete(obj);
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

        BSONObj* obj = new BSONObj();
        obj->add("_id", id);
        BSONObj* res = controller.findFirst("sp1.customer", obj);
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
        delete(obj);
    }

    log->stopTimeRecord();

    int secs = log->recordedTime().totalSecs();

    cout<< "finds " << ids.size() << ", secs: " << secs << endl;

    if (secs > 0) {
        cout << "Throughput: " << (ids.size() / secs) << " ops." << endl;
        cout << "------------------------------------------------------------" << endl;
    }
}

void testIndex(std::vector<std::string*> ids) {
    BPlusIndex tree;

    std::auto_ptr<Logger> log(getLogger(NULL));

    cout << "Staring index insert test" << endl;
    log->startTimeRecord();
    // Inserting
    int x = 0;
    for (std::vector<std::string*>::iterator i = ids.begin(); i != ids.end(); i++) {
        BSONObj* id = new BSONObj();
        id->add("_id", *i);
        tree.add(id, 0);
        x++;
    }
    log->stopTimeRecord();
    DTime time = log->recordedTime();
    cout << "Inserted " << x << " keys in " << time.toChar() << endl;

    cout << "Staring index search test" << endl;
    log->startTimeRecord();
    // Searching
    for (std::vector<std::string*>::iterator i = ids.begin(); i != ids.end(); i++) {
        BSONObj* id = new BSONObj();
        std::string* guid = *i;
        id->add("_id", guid);
        Index* index = tree.find(id);
        assert(index != NULL);
        BSONObj* key = index->key;
        assert(key != NULL);
        assert(key->getString("_id")->compare(*guid) == 0);
    }
    log->stopTimeRecord();
    time = log->recordedTime();
    cout << "Searched " << x << " keys in " << time.toChar() << endl;

}

void testSimpleIndex() {
    FileInputStream fis("simple.dat", "rb");
    std::vector<std::string*> ids;
    while (!fis.eof()) {
        ids.push_back(fis.readString());
    }
    fis.close();
    testIndex(ids);
}

void testComplexIndex() {
    FileInputStream fis("guids.txt", "rb");
    std::vector<std::string*> ids;
    while (!fis.eof()) {
        ids.push_back(fis.readString());
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
    fos.writeString(new std::string("1"));
    fos.writeString(new std::string("4"));
    fos.writeString(new std::string("8"));
    fos.writeString(new std::string("7"));
    fos.writeString(new std::string("9"));
    fos.writeString(new std::string("5"));
    fos.writeString(new std::string("6"));
    fos.writeString(new std::string("10"));
    fos.writeString(new std::string("2"));
    fos.writeString(new std::string("3"));
    fos.close();

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
