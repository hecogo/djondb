#include <iostream>
#include <dbcontroller.h>
#include <util.h>
#include <ctime>
#include "bson.h"

using namespace std;

DBController controller;

timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

int testInsert(BSONObj* o) {
    controller.insert("sp1.customer", o);
}

int testMassiveInsert(int inserts) {
    timespec ts1;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts1);

    for (int x = 0; x < inserts; x++) {
        BSONObj* obj = new BSONObj();
        obj->add("name", "John");
        obj->add("last", "Smith");
        testInsert(obj);
    }

    timespec ts2;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts2);

    timespec etime = diff(ts1, ts2);

    double secs = etime.tv_sec + ((double)etime.tv_nsec / 1000000000.0);
    cout<< "inserts " << inserts << ", secs: " << secs << endl;
}

int main()
{
    BSONObj* o = new BSONObj();
    o->add("name", "John");
    o->add("last", "Crossley");
    testInsert(o);
    delete(o);

    testMassiveInsert(1000);
    testMassiveInsert(10000);
    testMassiveInsert(100000);
//    testMassiveInsert(1000000);
//    testMassiveInsert(10000000);

    controller.close("sp1.customer");
    return 0;
}
