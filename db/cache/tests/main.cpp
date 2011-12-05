#include <iostream>

#include "cachemanager.h"
#include <assert.h>
#include <cpptest.h>

using namespace std;

class TestCacheSuite: public Test::Suite
{
public:
    TestCacheSuite()
    {
        TEST_ADD(TestCacheSuite::testCache);
    }

private:
    void testCache()
    {
        StructureCache* cache = new StructureCache();
        Structure* str = new Structure();
        str->add("name");
        str->add("lastName");
        long id = str->crc();
        CacheManager::structuresCache()->add(id, str);

        Structure* str2 = new Structure();
        str2->add("name");
        str2->add("lastName");
        long id2 = str->crc();
        CacheManager::structuresCache()->add(id2, str);

        Structure* s2 = (*CacheManager::structuresCache())[id];
        TEST_ASSERT (s2 == str);

        TEST_ASSERT (s2 != str2);
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
        ts.add(auto_ptr<Test::Suite>(new TestCacheSuite));
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
