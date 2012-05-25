#include <iostream>
#include <client/dbclient.h>
#include <util.h>
#include "fileinputstream.h"
#include "fileoutputstream.h"
#include <assert.h>

using namespace std;
using namespace mongo;

DBClientConnection c;

char* testInsert(char* host, int inserts) {


    Logger* log = getLogger(NULL);

    cout << "Starting " << endl;

    log->startTimeRecord();

    std::vector<std::string> ids;
    for (int x = 0; x < inserts; x++) {
        BSONObjBuilder b;
        std::auto_ptr<std::string> guid(uuid());
        b.append("id", *guid.get());

        int test = rand() % 10;
        if (test > 0) {
            ids.push_back(*guid.get());
        }
//        obj->add("name", "John");
        char* temp = (char*)malloc(2000);
        memset(temp, 0, 2000);
        memset(temp, 'a', 1999);
        int len = strlen(temp);
        b.append("content", temp);
        BSONObj obj = b.obj();
        free(temp);
        c.insert("tutorial.myns", obj);

        if ((inserts > 9) && (x % (inserts / 10)) == 0) {
            cout << x << " Records sent" << endl;
        }
    }
    FileOutputStream* fosIds = new FileOutputStream("results.txt", "wb");
    fosIds->writeInt(ids.size());
    for (std::vector<std::string>::iterator i2 = ids.begin(); i2!= ids.end(); i2++) {
        std::string s = *i2;
        fosIds->writeString(s);
    }
    fosIds->close();

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

    cout << "Closing the connection" << endl;

    delete(log);
    return 0;
}

void testFinds(char* host, int maxfinds) {
    Logger* log = getLogger(NULL);

    cout << "Starting " << endl;

    log->startTimeRecord();

    c.connect(host);

    FileInputStream* fisIds = new FileInputStream("results.txt", "rb");
    int x = 0;
    int count = fisIds->readInt();
    if ((maxfinds > -1) && (count > maxfinds)) {
        count = maxfinds;
    }
    cout << "Records to find: " << count << endl;
    for (x =0; x < count; x++) {
        std::string* guid = fisIds->readString();
        BSONObjBuilder b;
        b.append("id", *guid);

        BSONObj obj = b.obj();

        auto_ptr<DBClientCursor> cursor = c.query("tutorial.myns", obj);
        assert( cursor->more() );

        BSONObj resObj = cursor->next();

        assert(resObj.getStringField("id"));
        if ((count > 9) && (x % (count / 10)) == 0) {
            cout << x << " Records received" << endl;
        }
        delete guid;
    }
    cout << "Sending close connection command" << endl;
    cout << "all sent" << endl;

    log->stopTimeRecord();

    DTime rec = log->recordedTime();

    int secs = rec.totalSecs();
    cout<< "finds " << count << ", time: " << rec.toChar() << endl;

    if (secs > 0) {
        cout << "Throughput: " << (count / secs) << " ops." << endl;
    }
    cout << "------------------------------------------------------------" << endl;
    cout << "Ready to close the connection" << endl;
    getchar();

    cout << "Closing the connection" << endl;

    delete(log);
}

int main(int argc, char* args[])
{
    c.connect("localhost");

    int inserts = 0;
    bool insert = false;
    bool finds = false;
    bool error = false;
    int maxfinds = -1;
    for (int x = 1; x < argc; x++) {
        char* arg = args[x];
        if (strncmp(arg, "--finds", 7) == 0) {
            finds = true;
            char* findcount = strchr(arg, '=');
            if (findcount != NULL) {
                maxfinds = atoi(findcount+1);
            }
        } else if (strncmp(arg, "--inserts", 9) == 0) {
            inserts = true;
            char* insertcount = strchr(arg, '=');
            if (insertcount != NULL) {
                inserts = atoi(insertcount+1);
            } else {
                error = true;
                break;
            }
        } else {
            cout << "test: unrecognized option" << endl;
            error = true;
            break;
        }
    }
    if (!inserts && !finds) {
        error = true;
    }
    if (error) {
        cout << "Usage: test-network [--inserts=xx | --finds[=maxfinds] ]" << endl;
        return 1;
    }

    if (inserts) {
        cout << "Inserts " << inserts << endl;
        testInsert("localhost", inserts);
    }

    if (finds) {
        cout << "Finds " << endl;
        testFinds("localhost",maxfinds);
    }

    return 0;
}


