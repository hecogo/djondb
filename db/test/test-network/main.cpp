#include <iostream>
#include "networkservice.h"
#include "networkoutputstream.h"
#include "networkinputstream.h"
#include "commandwriter.h"
#include "util.h"
#include "bsonoutputstream.h"
#include "bsoninputstream.h"
#include "insertcommand.h"
#include "bson.h"
#include "config.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "command.h"

#ifdef WINDOWS
#include <Windows.h>
#endif
#include <assert.h>
#include <math.h>

using namespace std;


bool __running;
void *startSocketListener(void* arg);



void *startSocketListener(void* arg) {
    NetworkInputStream* nis = (NetworkInputStream*)arg;

    BSONInputStream* bis = new BSONInputStream(nis);
    while (__running) {
        std::auto_ptr<BSONObj> resObj(bis->readBSON());
        assert(resObj.get() != NULL);
        assert(resObj->has("_id"));
    }
}

char* sendReceive(char* host, int port, int inserts) {


    Logger* log = getLogger(NULL);

    cout << "Starting " << endl;

    log->startTimeRecord();
    __running = true;
    NetworkOutputStream* out = new NetworkOutputStream();
    int socket = out->open(host, port);
    NetworkInputStream* nis = new NetworkInputStream(socket);
    // nis->setNonblocking();
//    Thread* receiveThread = new Thread(&startSocketListener);
//    receiveThread->start(nis);
    out->writeChars("1.2.3", 5);
    BSONInputStream* bis = new BSONInputStream(nis);
//    BSONOutputStream* bsonOut = new BSONOutputStream(out);
    std::auto_ptr<CommandWriter> writer(new CommandWriter(out));
    for (int x = 0; x < inserts; x++) {
        std::auto_ptr<InsertCommand> cmd(new InsertCommand());

        BSONObj* obj = new BSONObj();
        std::string* guid = uuid();
        obj->add("_id", guid);
//        obj->add("name", "John");
        char* temp = (char*)malloc(2000);
        memset(temp, 0, 2000);
        memset(temp, 'a', 1999);
        int len = strlen(temp);
        obj->add("content", temp);
        //obj->add("last", "Smith");
        cmd->setBSON(obj);
        std::string* ns = new std::string("myns");
        cmd->setNameSpace(ns);
        writer->writeCommand(cmd.get());
//        std::auto_ptr<BSONObj> resObj(bis->readBSON());
//        assert(resObj.get() != NULL);
//        assert(resObj->has("_id"));
        if ((inserts > 9) && (x % (inserts / 10)) == 0) {
            cout << x << " Records sent" << endl;
        }
    }
    cout << "Sending close connection command" << endl;
    out->writeInt(CLOSECONNECTION);
    cout << "all sent" << endl;

    log->stopTimeRecord();

    DTime rec = log->recordedTime();

    int secs = rec.totalSecs();
    cout<< "inserts " << inserts << ", time: " << rec.toChar() << endl;

    if (secs > 0) {
        cout << "Throughput: " << (inserts / secs) << " ops." << endl;
    }
    cout << "------------------------------------------------------------" << endl;
    cout << "Ready to close the connection" << endl;
    getchar();
    __running = false;

    cout << "Closing the connection" << endl;
    out->closeStream();

    delete(log);
    return 0;
}

void testMassiveInsert(int inserts) {
//    FileOutputStream fos("temp.txt", "wb+");

    sendReceive("localhost",1243, inserts);
//    fos.close();

}

int main(int argc, char* args[])
{
//    NetworkService service;
//    service.start();
//
    int inserts;
    if (argc > 1) {
        cout << "Arg: " << args[1] << endl;
        inserts = atoi(args[1]);
    } else {
        inserts = 1;
    }
//    timespec t1;
//    clock_gettime(CLOCK_REALTIME, &t1);
//    sleep(2);
//    timespec t2;
//    clock_gettime(CLOCK_REALTIME, &t2);
//
//    timespec res = diff(t1, t2);
//    cout << "res: " << res.tv_sec << ":" << res.tv_nsec << endl;

    cout << "Inserts " << inserts << endl;
    testMassiveInsert(inserts);

//    getchar();
//
//    service.stop();

    return 0;
}


