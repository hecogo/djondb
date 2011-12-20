#include <iostream>
#include "../bson.h"
#include <string>
#include <string.h>
#include <cpptest.h>

using namespace std;

class TestBSONSuite : public Test::Suite
{
public:
    TestBSONSuite()
    {
        TEST_ADD(TestBSONSuite::testBSON)
        TEST_ADD(TestBSONSuite::testCopyBSON)
        TEST_ADD(TestBSONSuite::testParser)
    }

private:
    void testBSON()
    {
        BSONObj* obj = new BSONObj();
        // Add in
        obj->add("int", 1);
        obj->add("string", std::string("test"));
        obj->add("char*", (char*)"char*");
        obj->add("long", 1L);
        obj->add("double", 1.1);

		  BSONObj rel;
		  rel.add("innertext", std::string("inner text"));
		  obj->add("rel1", rel);


        TEST_ASSERT(obj->getInt("int") != NULL);
        TEST_ASSERT(*obj->getInt("int") == 1);

        TEST_ASSERT(obj->getString("string") != NULL);
        TEST_ASSERT(((std::string*)obj->getString("string"))->compare("test") == 0);

        TEST_ASSERT(obj->getChars("char*") != NULL);
        TEST_ASSERT(strcmp((char*) obj->getChars("char*"), "char*") == 0);

        TEST_ASSERT(obj->getLong("long") != NULL);
        TEST_ASSERT(*obj->getLong("long") == 1L);

        TEST_ASSERT(obj->getDouble("double") != NULL);
        TEST_ASSERT(*obj->getDouble("double") == 1.1);

        TEST_ASSERT(obj->getBSON("rel1") != NULL);
		  TEST_ASSERT(obj->getBSON("rel1")->getString("innertext")->compare("inner text") == 0);
		  delete obj;
    }

    void testCopyBSON()
    {
        BSONObj* objOrig = new BSONObj();
        // Add in
        objOrig->add("int", 1);
        objOrig->add("string", std::string("test"));
        objOrig->add("char*", (char*)"char*");
        objOrig->add("long", 1L);
        objOrig->add("double", 1.1);

		  BSONObj rel;
		  rel.add("innertext", std::string("inner text"));
		  objOrig->add("rel1", rel);


        BSONObj* obj = new BSONObj(*objOrig);
        delete objOrig;
        objOrig = NULL;

        TEST_ASSERT(obj->getInt("int") != NULL);
        TEST_ASSERT(*obj->getInt("int") == 1);

        TEST_ASSERT(obj->getString("string") != NULL);
        TEST_ASSERT(((std::string*)obj->getString("string"))->compare("test") == 0);

        TEST_ASSERT(obj->getChars("char*") != NULL);
        TEST_ASSERT(strcmp((char*) obj->getChars("char*"), "char*") == 0);

        TEST_ASSERT(obj->getLong("long") != NULL);
        TEST_ASSERT(*obj->getLong("long") == 1L);

        TEST_ASSERT(obj->getDouble("double") != NULL);
        TEST_ASSERT(*obj->getDouble("double") == 1.1);

        BSONObj* temp = obj->getBSON("rel1");
		  TEST_ASSERT(temp != NULL);
        TEST_ASSERT(obj->getBSON("rel1")->getString("innertext") != NULL);
		  TEST_ASSERT(obj->getBSON("rel1")->getString("innertext")->compare("inner text") == 0);

        delete obj;
    }

    void testParser()
    {
        BSONObj* obj = BSONParser::parse("{age: 1, name: 'John', salary: 3500.25}");//, rel1: {innertext: 'inner text'}
        TEST_ASSERT(obj->getInt("age") != NULL);
        TEST_ASSERT(*obj->getInt("age") == 1);
        TEST_ASSERT(obj->getChars("name") != NULL);
        TEST_ASSERT(strcmp(obj->getChars("name"), "John") == 0);

        TEST_ASSERT(obj->getDouble("salary") != NULL);
        TEST_ASSERT(*obj->getDouble("salary") == 3500.25);

		  TEST_ASSERT(obj->getBSON("rel1") != NULL);
		  TEST_ASSERT(obj->getBSON("rel1")->getString("innertext")->compare("inner text") == 0);

        delete obj;
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
        ts.add(auto_ptr<Test::Suite>(new TestBSONSuite));
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
