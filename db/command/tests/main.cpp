#include <iostream>
#include "bson.h"
#include "fileinputstream.h"
#include "fileoutputstream.h"
#include "bsonoutputstream.h"
#include "command.h"
#include "commandwriter.h"
#include "commandreader.h"
#include "insertcommand.h"
#include <cpptest.h>

#include <string>

class TestCommandSuite: public Test::Suite {
public:
   TestCommandSuite() {
      TEST_ADD(TestCommandSuite::testInsertCommand);	
	}

   void testInsertCommand() {
	   FileOutputStream* fos = new FileOutputStream("test.dat", "wb");
	   
      CommandWriter* commandWriter = new CommandWriter(fos);
		InsertCommand cmd;
		cmd.setNameSpace("test.namespace.db");
		BSONObj obj;
		obj.add("name", std::string("Cross"));
		obj.add("age", 18);
		cmd.setBSON(obj);
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
        ts.add(auto_ptr<Test::Suite>(new TestCommandSuite));
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
