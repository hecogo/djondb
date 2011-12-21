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
#include "bplusindex.cpp"
#include "math.h"
#include <cpptest.h>

using namespace std;

class TestDBSuite: public Test::Suite
{
public:
    TestDBSuite()
    {
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

        TEST_ADD(TestDBSuite::testInsertWithStringId);
        TEST_ADD(TestDBSuite::testInsertWithCharId);
        TEST_ADD(TestDBSuite::testInsertWithoutId);
        TEST_ADD(TestDBSuite::testSimpleIndex);
        TEST_ADD(TestDBSuite::testComplexIndex);
        controller.initialize();

        TEST_ADD(TestDBSuite::testFindPrevious);
        TEST_ADD(TestDBSuite::testMassiveInsert);
        TEST_ADD(TestDBSuite::testFinds);
		  TEST_ADD(TestDBSuite::testInsertComplexBSON);
		  TEST_ADD(TestDBSuite::testFindsByFilter);

        controller.shutdown();
    }
private:
    DBController controller;

    std::vector<std::string*> __ids;

private:
    void testInsert(BSONObj* o)
    {
        BSONObj* res = controller.insert("sp1.customer", o);
        delete res;
    }

    void testInsertWithStringId()
    {
		 cout << "testInsertWithStringId" << endl;
        BSONObj obj;
        std::string* id = uuid();
        obj.add("_id", *id);
        obj.add("name", "cross");
        delete id;
        BSONObj* res = controller.insert("sp1.customer", &obj);
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
        BSONObj* res = controller.insert("sp1.customer", &obj);
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
        BSONObj* res = controller.insert("sp1.customer", &obj);
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

		 BSONObj* res = controller.insert("sp1.customer", &obj);
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
            BSONObj* res = controller.findFirst("sp1.customer", &obj);
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
		 BSONObj* obj;
		 std::string customer = "{name: 'Juan', lastName:'Crossley'}";
		 obj = BSONParser::parse(customer);
		 controller.insert("find.filter", obj);
       delete obj;

		 BSONObj* filter = BSONParser::parse("{lastName: 'Crossley'}");

		 // Starting find by filter
		 std::vector<BSONObj*> found = controller.find("find.filter",*filter);
		 TEST_ASSERT(found.size() > 1); 
		 delete filter;
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
            BSONObj* res = controller.findFirst("sp1.customer", &obj);
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
            tree->add(id, 0);
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
