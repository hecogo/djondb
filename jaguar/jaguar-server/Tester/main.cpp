/*
 * File:   main.cpp
 * Author: cross
 *
 * Created on November 19, 2008, 12:25 AM
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include "util.h"
#include "dbjaguar.h"

#include "cpptest.h"
#include <stdio.h>
#include "time.h"

#define error(T) \
    cout << T << endl;

using namespace std;
using namespace dbjaguar;

class NetworkTestSuite : public Test::Suite
{
public:
    NetworkTestSuite()
    {
        TEST_ADD(NetworkTestSuite::sendreceive);
    }

private:
    void sendreceive()
    {
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;

        portno = 1043;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        server = gethostbyname("localhost");
        if (server == NULL)
        {
            fprintf(stderr, "ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) & serv_addr, sizeof (serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *) server->h_addr,
              (char *) & serv_addr.sin_addr.s_addr,
              server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd, (sockaddr *)  &serv_addr, sizeof (serv_addr)) < 0)
            TEST_FAIL("ERROR connecting");
//    long type = 2;
//    n = write(sockfd, (char*)&type, sizeof(type));
//
        char buffer[] = "0001ACT 03NEWDEFI011FFFF";
        n = write(sockfd, buffer, sizeof(buffer));
//        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
            TEST_FAIL("ERROR writing to socket");
        char rec[256];
        bzero(rec, 256);
        n = read(sockfd, rec, 255);
        if (n < 0)
            TEST_FAIL("ERROR reading from socket");
        cout << rec << endl;
        close(sockfd);
    }


};

class CommonTestSuite : public Test::Suite
{
public:
    CommonTestSuite()
    {
        TEST_ADD(CommonTestSuite::testStrtrim);
        TEST_ADD(CommonTestSuite::testStringTrim);
        TEST_ADD(CommonTestSuite::testCache);
        TEST_ADD(CommonTestSuite::testFormat);
    }

private:
    void testCache() {
        cache::CacheGroup* group = cache::getGlobalCache("test");
        char* val = "valor";
        group->add("test", val);

        char* res = (char*)group->get("test");

        TEST_ASSERT(res == val);
    }
    
    void testStrtrim()
    {
        char* s1 = "test ";
        char* se = "test";
        const char* sr = strtrim(s1);
        TEST_ASSERT(strcmp(se, sr) == 0);

        char* s2 = "  test       ";
        se = "  test";
        sr = strtrim(s2);
        TEST_ASSERT(strcmp(se, sr) == 0);

        char* s3 = "test";
        se = "test";
        sr = strtrim(s3);
        TEST_ASSERT(strcmp(se, sr) == 0);
    }

    void testStringTrim()
    {
        string s1 ("test ");
        string se1 ("test");
        trim(&s1);
        TEST_ASSERT(s1.compare(se1) == 0);

        string s2 ("  test     ");
        string se2 ("  test");
        trim(&s2);
        TEST_ASSERT(s2.compare(se2) == 0);

    }

    void testFormat() {
        char* s1 = "prueba 1 valor %d";
        string* res = format(s1, 10);
        TEST_ASSERT(res->compare("prueba 1 valor 10"));

        char* s2 = "prueba 2 valor %d %s";
        string* res2 = format(s2, 10, "test de texto");
        TEST_ASSERT(res2->compare("prueba 1 valor 10 test de texto"));
    }
};

class TestDB : public Test::Suite
{
public:
    TestDB()
    {
        TEST_ADD(TestDB::testConnection);
        TEST_ADD(TestDB::testResultSet);
        TEST_ADD(TestDB::testUpdate);
        TEST_ADD(TestDB::testStatement);
    }
private:
    void testStatement() {
        ConnectionPool* pool = new ConnectionPool();
        Connection* con = pool->getConnection("mysql;localhost;3304;jaguarmd", "root", "cross2000");
        Statement* stam1 = con->createStatement("CREATE TABLE test ( name int, t varchar(10))");
        stam1->executeUpdate();

        Statement* stam2 =  con->createStatement("INSERT INTO test (name, t) values (1, 'sta')");
        stam2->executeUpdate();

        Statement* stam3 = con->createStatement("INSERT INTO test (name, t) values (?, ?)");
        int* i = new int(1);
        stam3->setParameter(0, DBTYPE_LONG, i);

        char* t = "test char";
        stam3->setParameter(1, DBTYPE_STRING, t);
        stam3->executeUpdate();

        Statement* stam4 = con->createStatement("DROP TABLE test");
        stam4->executeUpdate();

        con->close();
    }
    
    void testConnection()
    {
        ConnectionPool* pool = new ConnectionPool();
        try
        {
            Connection* con = pool->getConnection("mysql;localhost;3304;jaguarmd", "root", "cross2000");
            con->close();
        }
        catch (DBException e)
        {
            TEST_FAIL(e.what());
        }
    }

    void testResultSet()
    {
        ConnectionPool* pool = new ConnectionPool();
        Connection* con = NULL;
        ResultSet* rs = NULL;
        try
        {
            con = pool->getConnection("mysql;localhost;3304;jaguarmd", "root", "cross2000");
            rs = con->executeQuery("select * from processdef");
            int x = 0;
            cout << "id\tdefname\t\tprocesstype\tmasterent" << endl;
            while ((*rs)++)
            {
                int* id = (int*)rs->get(0);
                string* defname = (string*)rs->get(1);
                int* processtype = (int*)rs->get(2);
                string* masterent = (string*)rs->get(3);
                cout << *id <<  *defname << "\t\t" << *processtype << "\t" << *masterent << endl;
            }
        }
        catch (DBException e)
        {
            TEST_FAIL(e.what());
        }
        if (rs)
            rs->close();
        if (con)
            con->close();
    }

    void testUpdate()
    {
        ConnectionPool* pool = new ConnectionPool();
        try
        {
            Connection* con = pool->getConnection("mysql;localhost;3304;jaguarmd", "root", "cross2000");
            con->executeUpdate("CREATE TABLE test ( name int)");
            con->executeUpdate("INSERT INTO test (name) values ('test')");
            con->executeUpdate("DROP TABLE test");
            con->close();
        }
        catch (DBException& e)
        {
            TEST_FAIL(e.what());
            return;
        }
    }
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

enum TestEnum
{
    A,B,C
};
/*
 *
 */
int main(int argc, char** argv)
{
    try
    {
//        cout << t << endl;
        // Demonstrates the ability to use multiple test suites
        //
        Test::Suite ts;
        ts.add(auto_ptr<Test::Suite>(new CommonTestSuite));
        ts.add(auto_ptr<Test::Suite>(new TestDB));
//        ts.add(auto_ptr<Test::Suite>(new WorkflowTestSuite));
        ts.add(auto_ptr<Test::Suite>(new NetworkTestSuite));

        // Run the tests
        //
        auto_ptr<Test::Output> output(cmdline(argc, argv));
        ts.run(*output, true);

        Test::HtmlOutput* const html = dynamic_cast<Test::HtmlOutput*>(output.get());
        if (html)
            html->generate(cout, true, "Jaguar tests");
    }
    catch (...)
    {
        cout << "unexpected exception encountered\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

