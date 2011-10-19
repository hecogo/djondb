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

int main(int argc, char* args[])
{
    if (argc < 2) {
        cout << "Usage: " << endl;
        cout << "    test-db inserts" << endl << endl;
        cout << "inserts:   number of inserts to execute" << endl << endl;
        return 0;
    }
    controller.initialize();

    testFindPrevious();
    int x = atoi(args[1]);
    testMassiveInsert(x);
    testFinds();

    controller.shutdown();
    return 0;
}
