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
#include <fileinputstream.h>
#include <fileoutputstream.h>
#include "bsonoutputstream.h"
#include "bsoninputstream.h"
#include "bson.h"
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
			TEST_ADD(TestFileSystemSuite::testBSONStreamsComplex);
			TEST_ADD(TestFileSystemSuite::testBSONStreamsArray);
			TEST_ADD(TestFileSystemSuite::testInnerArrays);
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

			TEST_ASSERT(obj->getString("string").compare("test") == 0);

			TEST_ASSERT(obj->getChars("char*") != NULL);
			TEST_ASSERT(strcmp((char*) obj->getChars("char*"), "char*") == 0);

			TEST_ASSERT(obj->getLong("long") != NULL);
			TEST_ASSERT(*obj->getLong("long") == 1L);

			TEST_ASSERT(obj->getDouble("double") != NULL);
			TEST_ASSERT(*obj->getDouble("double") == 1.1);

			fis->close();

		}

		void testInnerArrays() {
			// test bson inner arrays
			std::auto_ptr<BSONObj> objTest(BSONParser::parse("{age: 1, name: 'John', salary: 3500.25, rel1: [{innertext: 'inner text'}, {innertext: 'inner text'}, {innertext: 'inner text'}, {innertext: 'inner text'} ] }"));
			std::auto_ptr<FileOutputStream> fos(new FileOutputStream("bson.txt", "wb"));
			std::auto_ptr<BSONOutputStream> bsonOut(new BSONOutputStream(fos.get()));

			bsonOut->writeBSON(*objTest.get());

			fos->close();

			std::auto_ptr<FileInputStream> fis(new FileInputStream("bson.txt", "rb"));
			std::auto_ptr<BSONInputStream> bsonIn(new BSONInputStream(fis.get()));

			BSONObj* obj = bsonIn->readBSON();
			TEST_ASSERT(obj->getInt("age") != NULL);
			TEST_ASSERT(*obj->getInt("age") == 1);
			TEST_ASSERT(obj->getChars("name") != NULL);
			TEST_ASSERT(strcmp(obj->getChars("name"), "John") == 0);

			TEST_ASSERT(obj->getDouble("salary") != NULL);
			TEST_ASSERT(*obj->getDouble("salary") == 3500.25);

			TEST_ASSERT(obj->getBSONArray("rel1") != NULL);
			TEST_ASSERT(obj->getBSONArray("rel1")->length() == 4);
			TEST_ASSERT(obj->getBSONArray("rel1")->get(0)->getChars("innertext") != NULL);
			TEST_ASSERT(strcmp(obj->getBSONArray("rel1")->get(0)->getChars("innertext"), "inner text") == 0);

			delete obj;

		}

		void testBSONStreamsComplex()
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

			BSONObj inner;
			inner.add("int", 1);
			inner.add("string", std::string("test"));
			inner.add("char*", (char*)"char*");
			inner.add("long", 1L);
			inner.add("double", 1.1);

			obj->add("inner", inner);

			bsonOut->writeBSON(*obj);

			fos->close();

			obj.release();

			std::auto_ptr<FileInputStream> fis(new FileInputStream("bson.txt", "rb"));
			std::auto_ptr<BSONInputStream> bsonIn(new BSONInputStream(fis.get()));

			obj = std::auto_ptr<BSONObj>(bsonIn->readBSON());

			TEST_ASSERT(obj->getInt("int") != NULL);
			TEST_ASSERT(*obj->getInt("int") == 1);

			TEST_ASSERT(obj->getString("string").compare("test") == 0);

			TEST_ASSERT(obj->getChars("char*") != NULL);
			TEST_ASSERT(strcmp((char*) obj->getChars("char*"), "char*") == 0);

			TEST_ASSERT(obj->getLong("long") != NULL);
			TEST_ASSERT(*obj->getLong("long") == 1L);

			TEST_ASSERT(obj->getDouble("double") != NULL);
			TEST_ASSERT(*obj->getDouble("double") == 1.1);

			BSONObj* innerTest = obj->getBSON("inner");
			TEST_ASSERT(innerTest != NULL);

			TEST_ASSERT(innerTest->getInt("int") != NULL);
			TEST_ASSERT(*innerTest->getInt("int") == 1);

			TEST_ASSERT(innerTest->getString("string").compare("test") == 0);

			TEST_ASSERT(innerTest->getChars("char*") != NULL);
			TEST_ASSERT(strcmp((char*) innerTest->getChars("char*"), "char*") == 0);

			TEST_ASSERT(innerTest->getLong("long") != NULL);
			TEST_ASSERT(*innerTest->getLong("long") == 1L);

			TEST_ASSERT(innerTest->getDouble("double") != NULL);
			TEST_ASSERT(*innerTest->getDouble("double") == 1.1);

			fis->close();
		}

		void testBSONStreamsArray()
		{
			std::auto_ptr<FileOutputStream> fos(new FileOutputStream("bson.txt", "wb"));
			std::auto_ptr<BSONOutputStream> bsonOut(new BSONOutputStream(fos.get()));

			std::vector<BSONObj*> elements;
			for (int x = 0; x < 10; x++) {
				BSONObj* obj = new BSONObj();
				// Add in
				obj->add("int", 1);
				obj->add("string", std::string("test"));
				obj->add("char*", (char*)"char*");
				obj->add("long", 1L);
				obj->add("double", 1.1);

				elements.push_back(obj);
			}

			bsonOut->writeBSONArray(elements);

			fos->close();

			std::auto_ptr<FileInputStream> fis(new FileInputStream("bson.txt", "rb"));
			std::auto_ptr<BSONInputStream> bsonIn(new BSONInputStream(fis.get()));

			std::vector<BSONObj*> result = bsonIn->readBSONArray();

			TEST_ASSERT(result.size() == 10);
			for (std::vector<BSONObj*>::const_iterator i = result.begin(); i != result.end(); i++) {
				BSONObj* obj = *i;
				TEST_ASSERT(obj->getInt("int") != NULL);
				TEST_ASSERT(*obj->getInt("int") == 1);

				TEST_ASSERT(obj->getString("string").compare("test") == 0);

				TEST_ASSERT(obj->getChars("char*") != NULL);
				TEST_ASSERT(strcmp((char*) obj->getChars("char*"), "char*") == 0);

				TEST_ASSERT(obj->getLong("long") != NULL);
				TEST_ASSERT(*obj->getLong("long") == 1L);

				TEST_ASSERT(obj->getDouble("double") != NULL);
				TEST_ASSERT(*obj->getDouble("double") == 1.1);

			}

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
