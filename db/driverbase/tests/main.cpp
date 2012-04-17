// *********************************************************************************************************************
// file:
// author: Juan Pablo Crossley (crossleyjuan@gmail.com)
// created:
// updated:
// license:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// *********************************************************************************************************************

#include <iostream>
#include "djondb_client.h"

#include "fileoutputstream.h"
#include "fileinputstream.h"
#include "config.h"
#include "util.h"
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
			TEST_ADD(TestDriverBaseSuite::testFindByFilter);
//			TEST_ADD(TestDriverBaseSuite::testPerformance);

			TEST_ADD(TestDriverBaseSuite::testDropNamespace);
			//TEST_ADD(TestDriverBaseSuite::testTransactions);
		}

		void testDropNamespace() {
			Connection* conn = ConnectionManager::getConnection("localhost");

			conn->insert("db", "testdrop.namespace", "{ name: 'Test' }");

			bool result = conn->dropNamespace("db", "testdrop.namespace");

			TEST_ASSERT(result);

			BSONObj filter;
			std::vector<BSONObj*> testresult = conn->find("db", "testdrop.namespace", filter);

			TEST_ASSERT(testresult.size() == 0);
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

				conn->insert("db", "driverbase.test", obj);

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
			//getchar();
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

			cout << "Starting testFinds" << endl;

			__running = true;
			Connection* conn = ConnectionManager::getConnection("localhost");

			if (!conn->open()) {
				cout << "Cannot connect to localhost" << endl;
				exit(0);
			}

			BSONObj test;
			std::string* guid = uuid();
			test.add("_id", *guid);
			test.add("int", 1);
			test.add("long", 10L);
			test.add("char", "testing");

			conn->insert("db", "driver.test", test);

			log->debug("Data inserted");

			BSONObj* objResult = conn->findByKey("db", "driver.test", *guid);

			TEST_ASSERT(objResult != NULL);
			TEST_ASSERT(objResult->has("int"));
			TEST_ASSERT(*objResult->getInt("int") == 1);
			TEST_ASSERT(objResult->has("long"));
			TEST_ASSERT(*objResult->getLong("long") == 10);
			TEST_ASSERT(objResult->has("char"));
			TEST_ASSERT(strcmp(objResult->getChars("char"), "testing") == 0);

			__running = false;

			delete(log);
		}

		void testFindByFilter() {
			// Insert record to search for

			BSONObj* obj = BSONParser::parse("{name: 'Test'}");

			//delete id;

			Connection* conn = ConnectionManager::getConnection("localhost");

			if (!conn->open()) {
				cout << "Cannot connect to localhost" << endl;
				exit(0);
			}

			conn->insert("db", "test.filter2", *obj);

			// doing search
			//

			cout << "Testbyfilter" << endl;
			BSONObj objfilter;
			objfilter.add("name", "Test");
			std::vector<BSONObj*> result = conn->find("db", "test.filter2", objfilter);			
			TEST_ASSERT(result.size() > 0);

			BSONObj* objR = *result.begin();
			TEST_ASSERT(objR != NULL);
			TEST_ASSERT(objR->has("name"));
			TEST_ASSERT(strcmp(objR->getChars("name"), "Test") == 0);

			char* temp = objR->toChar();
			cout << "obj: " << temp << endl;
			delete objR;

		}

		void testPerformance() {
			Connection* conn = ConnectionManager::getConnection("localhost");

			// 1k inserts
			//
			Logger* log = getLogger(NULL);
			log->startTimeRecord();
			BSONObj obj;
			char* text = (char*)malloc(1001);
			memset(text, 0, 1001);
			memset(text, 'a', 1000);

			obj.add("text", text);

			int tests[] = { 10, 100, 1000, 10000, 1000000, 10000000};
			for (int i = 0; i < 6; i++) {
				cout << "Testing performance over: " << tests[i] << " inserts" << endl;
				for (int x = 0; x < tests[i]; x++) {
					std::string* uid = uuid();
					obj.add("_id", *uid);
					delete uid;
					conn->insert("db", "test.performance", obj);
				}

				log->stopTimeRecord();

				DTime time = log->recordedTime();

				if (time.totalSecs() > 0) {
					cout << "Performance over: " << tests[i] << " inserts:" << (tests[i] / time.totalSecs()) << endl;
				} else {
					cout << "Total time is not enough to do some calculations" << endl;
				}
				if ((time.totalSecs() > 0) && ((tests[i] / time.totalSecs()) < 16000))  {
					TEST_FAIL("Performance is not good enough");
					break;
				}
			}

			conn->close();

			free(text);
			delete log;
		}

		void testUpdate() {
			int maxupdates = 1;
			Logger* log = getLogger(NULL);

			cout << "Starting " << endl;

			log->startTimeRecord();
			__running = true;

			Connection* conn = ConnectionManager::getConnection("localhost");

			if (!conn->open()) {
				cout << "Cannot connect to localhost" << endl;
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

				conn->update("db", "driverbase.test", obj);

				if ((count > 9) && (x % (count / 10)) == 0) {
					cout << x << " Records received" << endl;
				}
			}

			log->stopTimeRecord();

			cout << "Executing a verification" << endl;

			for (std::vector<std::string>::iterator i = idsUpdated.begin(); i != idsUpdated.end(); i++) {
				std::string guid = *i;

				std::auto_ptr<BSONObj> resObj(conn->findByKey("db", "driverbase.test", guid));

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
			//getchar();
			__running = false;

			//    cout << "Closing the connection" << endl;
			//    conn->close();
			//
			//    delete conn;
			delete(log);
		}


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
