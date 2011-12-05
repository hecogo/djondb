#include <iostream>
#include <fileinputstream.h>
#include <fileoutputstream.h>
#include "bsonoutputstream.h"
#include "bsoninputstream.h"
#include "bsonobj.h"
#include <string.h>
#include <memory>
#include <cpptest.h>

using namespace std;

class TestFileSystemSuite: public Test::Suite
{

public:
    TestFileSystemSuite()
    {
        TEST_ADD(TestFileSystemSuite::testFileOutputStream);
        TEST_ADD(TestFileSystemSuite::testFileInputStream);
        TEST_ADD(TestFileSystemSuite::testBSONStreams);
    }

private:
    void testFileOutputStream()
    {
        FileOutputStream stream("test.txt", "wb");
        stream.writeChars("Hello World!", 12);
        stream.close();
    }

    void testFileInputStream()
    {
        FileInputStream stream("test.txt", "rb");
        char* text = stream.readChars();

        TEST_ASSERT(strcmp(text, "Hello World!") == 0);
        stream.close();
    }

    void testBSONStreams()
    {
        std::auto_ptr<FileOutputStream> fos(new FileOutputStream("bson.txt", "wb"));
        std::auto_ptr<BSONOutputStream> bsonOut(new BSONOutputStream(fos.get()));

        std::auto_ptr<BSONObj> obj(new BSONObj());
        // Add in
        obj->add("int", 1);
        obj->add("string", std::string("test"));
        obj->add("char*", (char*)"char*");
        obj->add("long", 1L);
        obj->add("double", 1.1);

        bsonOut->writeBSON(*obj);

        fos->close();

        obj.release();

        std::auto_ptr<FileInputStream> fis(new FileInputStream("bson.txt", "rb"));
        std::auto_ptr<BSONInputStream> bsonIn(new BSONInputStream(fis.get()));

        obj = std::auto_ptr<BSONObj>(bsonIn->readBSON());

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

        fis->close();
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
        ts.add(auto_ptr<Test::Suite>(new TestFileSystemSuite));
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
