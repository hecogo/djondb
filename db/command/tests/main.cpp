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
#include "bson.h"
#include "fileinputstream.h"
#include "fileoutputstream.h"
#include "bsonoutputstream.h"
#include "command.h"
#include "commandwriter.h"
#include "commandreader.h"
#include "insertcommand.h"
#include "updatecommand.h"
#include "findcommand.h"
#include "util.h"
#include <cpptest.h>

#include <string>

class TestCommandSuite: public Test::Suite {
	public:
		TestCommandSuite() {
			TEST_ADD(TestCommandSuite::testInsertCommand);	
			TEST_ADD(TestCommandSuite::testUpdateCommand);	
			TEST_ADD(TestCommandSuite::testFindCommand);	
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

			commandWriter->writeCommand(&cmd);

			fos->close();
			delete fos;
			delete commandWriter;

			FileInputStream* fis = new FileInputStream("test.dat", "rb");
			CommandReader* reader = new CommandReader(fis);
			InsertCommand* rdCmd = (InsertCommand*) reader->readCommand();
			TEST_ASSERT(rdCmd != NULL);
			TEST_ASSERT(rdCmd->nameSpace()->compare("test.namespace.db") == 0);
			BSONObj* objResult = rdCmd->bson();
			TEST_ASSERT(objResult != NULL);
			TEST_ASSERT(objResult->has("name"));	
			TEST_ASSERT(objResult->getString("name")->compare("Cross") == 0);
		}

		void testUpdateCommand() {
			FileOutputStream* fos = new FileOutputStream("test.dat", "wb");

			CommandWriter* commandWriter = new CommandWriter(fos);
			UpdateCommand cmd;
			cmd.setNameSpace("test.namespace.db");
			BSONObj obj;
			std::string* uid = uuid();
			obj.add("_id", *uid);
			delete uid;
			obj.add("name", std::string("Cross"));
			obj.add("age", 18);
			cmd.setBSON(obj);

			commandWriter->writeCommand(&cmd);

			fos->close();
			delete fos;
			delete commandWriter;

			FileInputStream* fis = new FileInputStream("test.dat", "rb");
			CommandReader* reader = new CommandReader(fis);
			UpdateCommand* rdCmd = (UpdateCommand*) reader->readCommand();
			TEST_ASSERT(rdCmd != NULL);
			TEST_ASSERT(rdCmd->nameSpace()->compare("test.namespace.db") == 0);
			BSONObj* objResult = rdCmd->bson();
			TEST_ASSERT(objResult  != NULL);
			TEST_ASSERT(objResult->has("name"));	
			TEST_ASSERT(objResult->getString("name")->compare("Cross") == 0);
		}

		void testFindCommand() {
			FileOutputStream* fos = new FileOutputStream("test.dat", "wb");

			CommandWriter* commandWriter = new CommandWriter(fos);
			FindCommand cmd;
			cmd.setNameSpace("test.namespace.db");
			BSONObj obj;
			std::string* uid = uuid();
			obj.add("_id", *uid);
			cmd.setBSON(obj);

			commandWriter->writeCommand(&cmd);

			fos->close();
			delete fos;
			delete commandWriter;

			FileInputStream* fis = new FileInputStream("test.dat", "rb");
			CommandReader* reader = new CommandReader(fis);
			FindCommand* rdCmd = (FindCommand*) reader->readCommand();
			TEST_ASSERT(rdCmd != NULL);
			TEST_ASSERT(rdCmd->nameSpace()->compare("test.namespace.db") == 0);
			BSONObj* objResult = rdCmd->bson();
			TEST_ASSERT(objResult  != NULL);
			TEST_ASSERT(objResult->has("_id"));	
			TEST_ASSERT(objResult->getString("_id")->compare(*uid) == 0);
			delete uid;
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
