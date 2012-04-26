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
#include <math.h>
#include "fileoutputstream.h"
#include "fileinputstream.h"
#include "bplusindex.h"
#include "filterparser.h"
#include "indexfactory.h"
#include "math.h"
#include <cpptest.h>

using namespace std;

class TestDBSuite: public Test::Suite
{
public:
    TestDBSuite()
    {
		 remove("sp1.customer.dat");
		 remove("sp1.customer.idx");
		 remove("find.filter.dat");
		 remove("find.filter.idx");

        FileOutputStream fos("simple.dat", "wb");
        fos.writeString(std::string("1"));
        fos.writeString(std::string("4"));
        fos.writeString(std::string("11"));
        fos.writeString(std::string("6"));
        fos.writeString(std::string("15"));
        fos.writeString(std::string("20"));
        fos.writeString(std::string("18"));
        fos.writeString(std::string("8"));
        fos.writeString(std::string("19"));
        fos.writeString(std::string("7"));
        fos.writeString(std::string("13"));
        fos.writeString(std::string("9"));
        fos.writeString(std::string("14"));
        fos.writeString(std::string("5"));
        fos.writeString(std::string("17"));
        fos.writeString(std::string("10"));
        fos.writeString(std::string("12"));
        fos.writeString(std::string("16"));
        fos.writeString(std::string("12"));
        fos.writeString(std::string("13"));
        fos.close();

		  TEST_ADD(TestDBSuite::testExpressions);
        TEST_ADD(TestDBSuite::testFilterExpressionParser);
        TEST_ADD(TestDBSuite::testFilterExpressionParserEquals);
        TEST_ADD(TestDBSuite::testSimpleIndex);
        TEST_ADD(TestDBSuite::testComplexIndex);
        TEST_ADD(TestDBSuite::testIndexFactory);
        TEST_ADD(TestDBSuite::testInsertWithStringId);
        TEST_ADD(TestDBSuite::testInsertWithCharId);
        TEST_ADD(TestDBSuite::testInsertWithoutId);
        controller.initialize();

        TEST_ADD(TestDBSuite::testFindPrevious);
        TEST_ADD(TestDBSuite::testMassiveInsert);
        TEST_ADD(TestDBSuite::testFinds);
		  TEST_ADD(TestDBSuite::testInsertComplexBSON);
		  TEST_ADD(TestDBSuite::testFindsByFilter);
		  TEST_ADD(TestDBSuite::testDropnamespace);

        controller.shutdown();
    }
private:
    DBController controller;

    std::vector<std::string*> __ids;

private:
    void testInsert(BSONObj* o)
	 {
		 BSONObj* res = controller.insert("dbtest", "sp1.customer", o);
		 delete res;
	 }

	 void testExpressions() {
		 cout << "testExpressions" << endl;
		 BSONObj dummy;
		 ConstantExpression exp("35");
		 ExpressionResult* result = exp.eval(dummy);

		 TEST_ASSERT(result->type() == RT_INT);
		 int* i = (int*)result->value();
		 TEST_ASSERT(*i == 35);

		 ConstantExpression exp2("3.324");
		 ExpressionResult* result2 = exp2.eval(dummy);
		 TEST_ASSERT(result2->type() == RT_DOUBLE);
		 double* d = (double*)result2->value();
		 TEST_ASSERT(*d == 3.324);

		 ConstantExpression exp3("'Test'");
		 ExpressionResult* result3 = exp3.eval(dummy);
		 TEST_ASSERT(result3->type() == RT_STRING);
		 std::string* s = (std::string*)result3->value();
		 TEST_ASSERT(s != NULL);
		 TEST_ASSERT(s->compare("Test") == 0);

		 BSONObj obj;
		 obj.add("age", 35);
		 obj.add("name", "John");
		 BSONObj inner;
		 inner.add("i", 100);
		 obj.add("child", inner);

		 SimpleExpression exp4("age");
		 ExpressionResult* result4 = exp4.eval(obj);
		 TEST_ASSERT(result4->type() == RT_INT);
		 int* i2 = (int*)result4->value();
		 TEST_ASSERT(i2 != NULL);
		 TEST_ASSERT(*i2 == 35);

		 SimpleExpression exp5("name");
		 ExpressionResult* result5 = exp5.eval(obj);
		 std::string* s2 = (std::string*)result5->value();
		 TEST_ASSERT(s2 != NULL);
		 TEST_ASSERT(s2->compare("John") == 0);
		 delete result5;
		 
		 SimpleExpression exp6("child.i");
		 ExpressionResult* result6 = exp6.eval(obj);
		 int* i3 = (int*)result6->value();
		 TEST_ASSERT(i3 != NULL);
		 TEST_ASSERT(*i3 == 100);

		 BinaryExpression exp7(FO_EQUALS);
		 exp7.push(new SimpleExpression("age"));
		 exp7.push(new ConstantExpression("35"));
		 ExpressionResult* result7 = exp7.eval(obj);
		 TEST_ASSERT(result7->type() == RT_BOOLEAN);
		 bool* bresult7 = (bool*)result7->value();
		 TEST_ASSERT(*bresult7 == true);
	 }

	 void testFilterExpressionParser() {
		 cout << "testFilterExpressionParser" << endl;
		 BSONObj obj;
		 obj.add("age", 35);
		 obj.add("state", 1);

		 FilterParser* parser = FilterParser::parse("$'age'");
		 ExpressionResult* result = parser->eval(obj);

		 TEST_ASSERT(result->type() == RT_INT);
		 int* test = (int*)result->value();

		 TEST_ASSERT(test != NULL);
		 TEST_ASSERT(*test == 35);

		 delete parser;

		 parser = FilterParser::parse("$'age' == 35");
		 result = parser->eval(obj);
		 TEST_ASSERT(result->type() == RT_BOOLEAN);
		 bool* bres = (bool*)result->value();
		 TEST_ASSERT(*bres);

		 parser = FilterParser::parse("($'age' == 35 )");
		 result = parser->eval(obj);
		 TEST_ASSERT(result->type() == RT_BOOLEAN);
		 bres = (bool*)result->value();
		 TEST_ASSERT(*bres);

		 parser = FilterParser::parse("(($'age' == 35 ) and ($'state' == 1 l))");
		 result = parser->eval(obj);
		 TEST_ASSERT(result->type() == RT_BOOLEAN);
		 bres = (bool*)result->value();
		 TEST_ASSERT(*bres);

	 }

	 void testFilterExpressionParserEquals() {
		 cout << "testFilterExpressionParserEquals" << endl;
		 BSONObj obj;
		 obj.add("age", 35);

		 FilterParser* parser = FilterParser::parse("$'age' == $'age'");
		 /* 
			 BSONContent* content = (BSONContent*)parser->eval(obj);

			 int* test = *content;

			 TEST_ASSERT(test != NULL);
			 TEST_ASSERT(*test == 35);
			 */
		 delete parser;

	 }

	 void testInsertWithStringId()
	 {
		 cout << "testInsertWithStringId" << endl;
		 BSONObj obj;
		 std::string* id = uuid();
		 obj.add("_id", *id);
		 obj.add("name", "cross");
		 delete id;
		 BSONObj* res = controller.insert("dbtest", "sp1.customer", &obj);
		 if (res != NULL)
		 {
			 delete res;
		 }
	 }

	 void testInsertWithCharId()
	 {
		 cout << "testInsertWithCharId" << endl;
		 BSONObj obj;
		 std::string* id = uuid();
		 obj.add("_id", id->c_str());
		 obj.add("name", "cross");
		 delete id;
		 BSONObj* res = controller.insert("dbtest", "sp1.customer", &obj);
		 if (res != NULL)
		 {
			 delete res;
		 }
	 }

	 void testInsertWithoutId()
	 {
		 cout << "testInsertWithoutId" << endl;
		 BSONObj obj;
		 obj.add("name", "cross");
		 BSONObj* res = controller.insert("dbtest", "sp1.customer", &obj);
		 TEST_ASSERT(res != NULL);
		 TEST_ASSERT(res->has("_id"));
		 delete res;
	 }

	 void testInsertComplexBSON() {
		 cout << "testInsertComplexBSON" << endl;
		 BSONObj obj;
		 obj.add("int", 1);
		 obj.add("char", "test");

		 BSONObj inner;
		 inner.add("int", 2);
		 inner.add("char", "testInner");
		 obj.add("inner", inner);

		 BSONObj* res = controller.insert("dbtest", "sp1.customer", &obj);
		 TEST_ASSERT(res != NULL);
		 TEST_ASSERT(res->has("_id"));
		 delete res;
	 }

	 void testMassiveInsert()
	 {
		 cout << "testMassiveInsert" << endl;
		 int inserts = 1000;
		 std::auto_ptr<Logger> log(getLogger(NULL));

		 log->startTimeRecord();

		 FileOutputStream fos("temp.txt", "wb+");

		 for (int x = 0; x < inserts; x++)
		 {
			 BSONObj* obj = new BSONObj();
			 obj->add("name", "John");
			 char temp[700];
			 memset(temp, 0, 699);
			 memset(temp, 'a', 700);
			 obj->add("content", std::string(temp));
			 obj->add("last", std::string("Smith"));
			 testInsert(obj);

			 int test = rand() % 10;
			 if (test > 0)
			 {
				 __ids.push_back(new std::string(((std::string*)obj->getString("_id"))->c_str()));
				 fos.writeString(*obj->getString("_id"));
			 }
			 if ((x % 1000000) == 0)
			 {

				 cout<< "inserts " << x << endl;
			 }
			 delete obj;
		 }
		 fos.close();

		 log->stopTimeRecord();

		 int secs = log->recordedTime().totalSecs();

		 cout<< "inserts " << inserts << ", secs: " << secs << endl;

		 if (secs > 0)
		 {
			 // If throughtput is too small fail
			 TEST_ASSERT((inserts / secs) > 10000);
			 cout << "Throughput: " << (inserts / secs) << " ops." << endl;
			 cout << "------------------------------------------------------------" << endl;
		 }
	 }

	 void testFinds()
	 {
		 cout << "testFinds" << endl;

		 std::auto_ptr<Logger> log(getLogger(NULL));

		 log->startTimeRecord();

		 for (std::vector<string*>::iterator i = __ids.begin(); i != __ids.end(); i++)
		 {
			 string* id = *i;

			 BSONObj obj;
			 obj.add("_id", *id);
			 BSONObj* res = controller.findFirst("dbtest", "sp1.customer", &obj);
			 std::string* id2 = res->getString("_id");
			 if ((id2 == NULL) || (id2->compare(*id) != 0))
			 {
				 TEST_FAIL("id not found");
			 }
			 delete res;
		 }

		 log->stopTimeRecord();

		 int secs = log->recordedTime().totalSecs();

		 if (secs > 0)
		 {
			 TEST_ASSERT((__ids.size() / secs) > 30);
			 cout << "Throughput: " << (__ids.size() / secs) << " ops." << endl;
			 cout << "------------------------------------------------------------" << endl;
		 }
	 }

	 void testFindsByFilter()
	 {
		 cout << "testFindsByFilter" << endl;
		 // Insert some data
		 //
		 controller.insert("dbtest", "find.filter", BSONParser::parse("{name: 'Juan', lastName:'Crossley'}"));
		 controller.insert("dbtest", "find.filter", BSONParser::parse("{name: 'Pepe', lastName:'Crossley'}"));
		 controller.insert("dbtest", "find.filter", BSONParser::parse("{name: 'Juan', lastName:'Smith'}"));
		 controller.insert("dbtest", "find.filter", BSONParser::parse("{name: 'Juan', lastName:'Clark'}"));
		 controller.insert("dbtest", "find.filter", BSONParser::parse("{name: 'Juan', lastName:'Crossley'}"));
		 controller.insert("dbtest", "find.filter", BSONParser::parse("{name: 'Juan', lastName:'Crossley'}"));
		 controller.insert("dbtest", "find.filter", BSONParser::parse("{name: 'Juan', lastName:'Crossley'}"));
		 controller.insert("dbtest", "find.filter", BSONParser::parse("{name: 'Juan', lastName:'Last'}"));

		 BSONObj* filter = BSONParser::parse("{lastName: 'Crossley'}");

		 // Starting find by filter
		 std::vector<BSONObj*> found = controller.find("dbtest", "find.filter",*filter);
		 TEST_ASSERT(found.size() == 5); 
		 delete filter;

		 found = controller.find("dbtest", "find.filter", *BSONParser::parse("{}"));
		 TEST_ASSERT(found.size() == 8); 

		 found = controller.find("dbtest", "find.filter", *BSONParser::parse("{name: 'Juan'}"));
		 TEST_ASSERT(found.size() == 7); 

		 found = controller.find("dbtest", "find.filter", *BSONParser::parse("{name: 'Juan', lastName: 'Smith'}"));
		 TEST_ASSERT(found.size() == 1); 

		 found = controller.find("dbtest", "find.filter", *BSONParser::parse("{name: 'Juan', lastName: 'Last'}"));
		 TEST_ASSERT(found.size() == 1); 
	 }

	 void testFindPrevious()
	 {
		 cout << "testFindPrevious" << endl;
		 std::auto_ptr<Logger> log(getLogger(NULL));

		 FileInputStream fis("temp.txt", "rb");
		 std::vector<std::string*> ids;
		 while (!fis.eof())
		 {
			 ids.push_back(fis.readString());
		 }
		 fis.close();

		 log->startTimeRecord();

		 for (std::vector<string*>::iterator i = ids.begin(); i != ids.end(); i++)
		 {
			 string* id = *i;

			 BSONObj obj;
			 obj.add("_id", *id);
			 BSONObj* res = controller.findFirst("dbtest", "sp1.customer", &obj);
			 if (res == NULL)
			 {
				 TEST_FAIL("Looking for a previous id does not returned any match");
				 break;
			 }
			 else
			 {
				 std::string* id2 = res->getString("_id");
				 //        cout << "Looking for: " << *id << endl;
				 //        cout << "Found        " << *id2 << endl;
				 if ((id2 == NULL) || (id2->compare(*id) != 0))
				 {
					 TEST_FAIL("findFirst returned an incorrect result");
				 }
				 delete res;
			 }
		 }

		 log->stopTimeRecord();

		 int secs = log->recordedTime().totalSecs();

		 if (secs > 0)
		 {
			 TEST_ASSERT((ids.size() / secs) > 30);
			 cout << "Throughput: " << (ids.size() / secs) << " ops." << endl;
			 cout << "------------------------------------------------------------" << endl;
		 }
	 }

	 void testIndex(std::vector<std::string> ids)
	 {
		 std::auto_ptr<BPlusIndex> tree(new BPlusIndex());

		 std::auto_ptr<Logger> log(getLogger(NULL));

		 log->startTimeRecord();
		 // Inserting
		 int x = 0;
		 for (std::vector<std::string>::iterator i = ids.begin(); i != ids.end(); i++)
		 {
			 BSONObj id;
			 id.add("_id", *i);
			 tree->add(id, 0, 0);
			 x++;
		 }
		 log->stopTimeRecord();
		 DTime time = log->recordedTime();

		 log->startTimeRecord();
		 while (ids.size() > 0)
		 {
			 int pos = rand() % ids.size();
			 while (pos > ids.size())
			 {
				 pos = rand() % ids.size();
			 }
			 std::vector<std::string>::iterator i = ids.begin() + pos;
			 std::string guid = *i;

			 BSONObj id;
			 id.add("_id", guid);
			 Index* index = tree->find(id);
			 TEST_ASSERT(index != NULL);
			 BSONObj* key = index->key;
			 TEST_ASSERT(key != NULL);
			 TEST_ASSERT(key->getString("_id") != NULL);
			 TEST_ASSERT(key->getString("_id")->compare(guid) == 0);

			 ids.erase(i);
		 }
		 log->stopTimeRecord();
		 time = log->recordedTime();
	 }

	 void testSimpleIndex()
	 {
		 cout << "testSimpleIndex" << endl;
		 FileInputStream fis("simple.dat", "rb");
		 std::vector<std::string> ids;
		 while (!fis.eof())
		 {
			 std::string* s = fis.readString();
			 ids.push_back(*s);
			 delete s;
		 }
		 fis.close();
		 testIndex(ids);
	 }

	 void testComplexIndex()
	 {
		 cout << "testComplexIndex" << endl;
		 FileInputStream fis("guids.txt", "rb");
		 std::vector<std::string> ids;
		 while (!fis.eof())
		 {
			 std::string* s= fis.readString();
			 ids.push_back(*s);
			 delete s;
		 }
		 fis.close();
		 testIndex(ids);
	 }

	 void testIndexFactory() {
		 cout << "testIndexFactory" << endl;
		 BSONObj test;
		 test.add("_id", "1");

		 IndexAlgorithm* index = IndexFactory::indexFactory.index("dbtest", "ns.a", test);
		 TEST_ASSERT(index != NULL);

		 // Let's check if the factory returns the same instance for the same key
		 IndexAlgorithm* indexCompare = IndexFactory::indexFactory.index("dbtest", "ns.a", test);
		 TEST_ASSERT(index == indexCompare);

		 // Let's change the keys and test if a new IndexAlgorithm will be returned
		 BSONObj test2;
		 test2.add("key", "a");
		 IndexAlgorithm* indexCompare2 = IndexFactory::indexFactory.index("dbtest", "ns.a", test2);
		 TEST_ASSERT(index != indexCompare2);

		 // Checking the contains method
		 bool res = IndexFactory::indexFactory.containsIndex("dbtest", "ns.a", test);
		 TEST_ASSERT(res);

		 BSONObj test3;
		 test3.add("nkey", "b");
		 bool res2 = IndexFactory::indexFactory.containsIndex("dbtest", "ns.a", test3);
		 TEST_ASSERT(!res2);
	 }

	 void testDropnamespace()
	 {
		 cout << "testDropnamespace" << endl;
		 BSONObj obj;
		 obj.add("name", "Test");

		 BSONObj* res = controller.insert("dbtest", "ns.drop", &obj);

		 bool result = controller.dropNamespace("dbtest", "ns.drop");
		 TEST_ASSERT(result);

		 BSONObj filter;

		 std::vector<BSONObj*> finds = controller.find("dbtest", "ns.drop", filter);

		 TEST_ASSERT(finds.size() == 0);
		 delete res;
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
		ts.add(auto_ptr<Test::Suite>(new TestDBSuite));
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
