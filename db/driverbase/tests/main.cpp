#include <iostream>
#include "djondb_client.h"

#include "fileoutputstream.h"
#include "fileinputstream.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cpptest.h> 

using namespace std; 
using namespace djondb;

bool __running;
void *startSocketListener(void* arg);


void *startSocketListener(void* arg) {
	/*
		NetworkInputStream* nis = (NetworkInputStream*)arg;

		BSONInputStream* bis = new BSONInputStream(nis);
		while (__running) {
		std::auto_ptr<BSONObj> resObj(bis->readBSON());
		TEST_ASSERT(resObj.get() != NULL);
		TEST_ASSERT(resObj->has("_id"));
		}
		*/
}

class TestDriverBaseSuite: public Test::Suite {
	private:
		char* _host;
		int _port;

	public:

		TestDriverBaseSuite() {
			_host = "localhost";
			_port = 1243;
			TEST_ADD(TestDriverBaseSuite::testInsert);
			TEST_ADD(TestDriverBaseSuite::testFinds);
			TEST_ADD(TestDriverBaseSuite::testUpdate);
		}

		void testInsert() {
			int inserts = 1;

			Logger* log = getLogger(NULL);

			cout << "Starting " << endl;

			log->startTimeRecord();
			__running = true;

			Connection* conn = ConnectionManager::getConnection(std::string(_host));

			if (!conn->open()) {
				cout << "Could not connect to " << _host << endl;
				exit(0);
			}
			std::vector<std::string> ids;
			for (int x = 0; x < inserts; x++) {

				BSONObj obj;
				std::auto_ptr<std::string> guid(uuid());
				obj.add("_id", *guid.get());
				int test = rand() % 10;
				if (test > 0) {
					ids.push_back(*guid.get());
				}
				//        obj->add("name", "John");
				char* temp = (char*)malloc(2000);
					memset(temp, 0, 2000);
				memset(temp, 'a', 1999);
				int len = strlen(temp);
				obj.add("content", temp);
				free(temp);

				conn->insert("driverbase.test", obj);

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
			//    getchar();
			__running = false;

			//    cout << "Closing the connection" << endl;
			//    conn->close();
			//
			//    delete conn;
			delete(log);
		}

		void testFinds() {
			int maxfinds = 1;
			Logger* log = getLogger(NULL);

			cout << "Starting " << endl;

			log->startTimeRecord();
			__running = true;
			Connection* conn = ConnectionManager::getConnection("local_host");

			if (!conn->open()) {
				cout << "Cannot connect to local_host" << endl;
				exit(0);
			}
			FileInputStream* fisIds = new FileInputStream("results.txt", "rb");
			int x = 0;
			int count = fisIds->readInt();
			if ((maxfinds > -1) && (count > maxfinds)) {
				count = maxfinds;
			}
			cout << "Records to find: " << count << endl;

			for (x =0; x < count; x++) {
				std::string* guid = fisIds->readString();

				std::auto_ptr<BSONObj> resObj(conn->findByKey("driverbase.test", *guid));

				TEST_ASSERT(resObj.get() != NULL);
				TEST_ASSERT(resObj->has("_id"));
				TEST_ASSERT(resObj->has("content"));

				char* temp = (char*)malloc(2000);
					memset(temp, 0, 2000);
				memset(temp, 'a', 1999);
				TEST_ASSERT(strcmp(resObj->getChars("content"), temp) == 0);
				free(temp);
				if ((count > 9) && (x % (count / 10)) == 0) {
					cout << x << " Records received" << endl;
				}
				delete guid;
			}
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
			//    getchar();
			__running = false;

			//    cout << "Closing the connection" << endl;
			//    conn->close();
			//
			//    delete conn;

			delete(log);
		}

		void testUpdate() {
         int maxupdates = 1;
			Logger* log = getLogger(NULL);

			cout << "Starting " << endl;

			log->startTimeRecord();
			__running = true;

			Connection* conn = ConnectionManager::getConnection("local_host");

			if (!conn->open()) {
				cout << "Cannot connect to local_host" << endl;
				exit(0);
			}
			FileInputStream* fisIds = new FileInputStream("results.txt", "rb");
			int x = 0;
			int count = fisIds->readInt();
			if ((maxupdates > -1) && (count > maxupdates)) {
				count = maxupdates;
			}
			cout << "Records to update: " << count << endl;

			std::vector<std::string> idsUpdated;
			for (x =0; x < count; x++) {
				std::auto_ptr<std::string> guid(fisIds->readString());

				BSONObj obj;
				obj.add("_id", *guid.get());

				idsUpdated.push_back(*guid.get());
				char* temp = (char*)malloc(100);
					memset(temp, 0, 100);
				memset(temp, 'b', 99);
				int len = strlen(temp);
				obj.add("content", temp);
				free(temp);

				conn->update("driverbase.test", obj);

				if ((count > 9) && (x % (count / 10)) == 0) {
					cout << x << " Records received" << endl;
				}
			}

			log->stopTimeRecord();

			cout << "Executing a verification" << endl;

			for (std::vector<std::string>::iterator i = idsUpdated.begin(); i != idsUpdated.end(); i++) {
				std::string guid = *i;

				std::auto_ptr<BSONObj> resObj(conn->findByKey("driverbase.test", guid));

				TEST_ASSERT(resObj.get() != NULL);
				TEST_ASSERT(resObj->has("_id"));
				TEST_ASSERT(resObj->has("content"));

				char* temp = (char*)malloc(100);
					memset(temp, 0, 100);
				memset(temp, 'b', 99);
				TEST_ASSERT(strcmp(resObj->getChars("content"), temp) == 0);
				free(temp);
			}
			DTime rec = log->recordedTime();

			int secs = rec.totalSecs();
			cout<< "finds " << count << ", time: " << rec.toChar() << endl;

			if (secs > 0) {
				cout << "Throughput: " << (count / secs) << " ops." << endl;
			}
			cout << "------------------------------------------------------------" << endl;
			cout << "Ready to close the connection" << endl;
			//    getchar();
			__running = false;

			//    cout << "Closing the connection" << endl;
			//    conn->close();
			//
			//    delete conn;
			delete(log);
		}
		/*
			int main(int argc, char* args[])
			{
		//    NetworkService service;
		//    service.start();
		//
		int inserts;
		bool insert = false;
		bool finds = false;
		bool updates = false;
		bool error = false;
		int maxfinds = -1;
		int maxupdates = -1;
		if (argc < 2) {
		cout << "No command specified" << endl;
		error = true;
		}
		for (int x = 1; x < argc; x++) {
		if (strncmp(args[x], "--insert", 8) == 0) {
		insert = true;
		char* val = strchr(args[x], '=');
		if (val == NULL) {
		cout << "Incorrect syntax, expected --insert=xxx" << endl;
		error = true;
		} else {
		inserts = atoi(val + 1);
		}
		} else if (strncmp(args[x], "--finds", 7) == 0) {
		finds = true;
		char* val = strchr(args[x], '=');
		if (val != NULL) {
		maxfinds = atoi(val+1);
		}
		} else if (strncmp(args[x], "--updates", 9) == 0) {
		updates = true;
		char* val = strchr(args[x], '=');
		if (val != NULL) {
		maxupdates = atoi(val+1);
		}
		} else {
		cout << "Incorrect command " << args[x] << endl;
		error = true;
		}
		}
		if (error) {
		cout << "Usage: test-network [--inserts=xxxx] [--finds[=maxfinds] ] [--update[=maxupdates] ]" << endl;
		return;
		}

		if (insert) {
		cout << "Inserts " << inserts << endl;
		testInsert("local_host",1243, inserts);
		}

		if (finds) {
		cout << "Finds " << endl;
		testFinds("local_host",1243, maxfinds);
		}

		if (updates) {
		cout << "Updates " << endl;
		testUpdate("local_host",1243, maxupdates);
		}

		if (!error) {
		cout << "Press any key to close the connections" << endl;
		getchar();
		}
		Connection* conn = ConnectionManager::getConnection("local_host");
		if (conn->isOpen()) {
		conn->close();
delete conn;
}
}
*/
};


enum OutputType
{
    Compiler,
    Html,
    TextTerse,
    TextVerbose
};

static void
usage()
{
    cout << "usage: mytest [MODE]\n"
         << "where MODE may be one of:\n"
         << "  --compiler\n"
         << "  --html\n"
         << "  --text-terse (default)\n"
         << "  --text-verbose\n";
    exit(0);
}

static auto_ptr<Test::Output>
cmdline(int argc, char* argv[])
{
    if (argc > 2)
        usage(); // will not return

    Test::Output* output = 0;

    if (argc == 1)
        output = new Test::TextOutput(Test::TextOutput::Verbose);
    else
    {
        const char* arg = argv[1];
        if (strcmp(arg, "--compiler") == 0)
            output = new Test::CompilerOutput;
        else if (strcmp(arg, "--html") == 0)
            output =  new Test::HtmlOutput;
        else if (strcmp(arg, "--text-terse") == 0)
            output = new Test::TextOutput(Test::TextOutput::Terse);
        else if (strcmp(arg, "--text-verbose") == 0)
            output = new Test::TextOutput(Test::TextOutput::Verbose);
        else
        {
            cout << "invalid commandline argument: " << arg << endl;
            usage(); // will not return
        }
    }

    return auto_ptr<Test::Output>(output);
}

// Main test program
//
int main(int argc, char* argv[])
{
    try
    {
        // Demonstrates the ability to use multiple test suites
        //
        Test::Suite ts;
        ts.add(auto_ptr<Test::Suite>(new TestDriverBaseSuite));
//        ts.add(auto_ptr<Test::Suite>(new CompareTestSuite));
//        ts.add(auto_ptr<Test::Suite>(new ThrowTestSuite));

        // Run the tests
        //
        auto_ptr<Test::Output> output(cmdline(argc, argv));
        ts.run(*output, true);

        Test::HtmlOutput* const html = dynamic_cast<Test::HtmlOutput*>(output.get());
        if (html)
            html->generate(cout, true, "MyTest");
    }
    catch (...)
    {
        cout << "unexpected exception encountered\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
