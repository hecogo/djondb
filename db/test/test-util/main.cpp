#include <iostream>
#include <util.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int testDates() {
    cout << "Testing date functions" << endl;
    DateTime dt = DateTime::today(true);

    cout << "Current date: " << dt.toChar() << endl;

    DateTime dt2 = dt.addDays(1);
    cout << dt2.toChar() << endl;

    assert((dt.getDay() + 1) == dt2.getDay());

    // testing day of the week
    dt = DateTime(2011, 9, 12);
    assert(dt.dayOfTheWeek() == 1);

    // testing day of the week "complex", 29 of febr
    dt = DateTime(2008, 2, 29);
    assert(dt.dayOfTheWeek() == 5);

    // diff
    dt = DateTime(2011, 2, 10);
    dt2 = DateTime(2011, 3, 1);
    int diff = dt2.daysTo(dt);
    assert(diff == 19);

    cout << "out Testing date functions" << endl;
    return 0;
}

int testTimes() {
    // Testing diff
    DTime t(15, 40, 0);
    DTime t2(16, 20, 0);
    DTime res = t2 - t;

    assert((res.hour() == 0) && (res.minutes() == 40) && (res.seconds() == 0));

    res = t2 - 200;
    assert((res.hour() == 16) && (res.minutes() == 16) && (res.seconds() == 40));
    // teting add
    return 0;
}

int testStrings() {
    // Copy chars
    char* test = "Hello world!";
    char* res = strcpy(test, strlen(test));

    assert(strcmp(test, res) == 0);
    assert(test != res);
    free(res);

    //copy string
    std::string s = "Hello world!";
    res = strcpy(s);
    assert(s.compare(res) == 0);

    // ends with
    bool com = endsWith("test.tex", ".tex");
    assert(com);
    com = endsWith("test.ss", "test");
    assert(!com);

    // tokenizer
    std::vector<std::string*>* token = tokenizer("test,other,and 1 more", ",");
    assert(token->size() == 3);
    assert(token->at(0)->compare("test") == 0);
    assert(token->at(1)->compare("other") == 0);
    assert(token->at(2)->compare("and 1 more") == 0);
    delete(token);

    // format
    std::string sformat = format("test %d %s %5.4f", 10, "Hello World!", 3.14159);
    assert(sformat.compare("test 10 Hello World! 3.1416") == 0);

    // toString
    std::string s2 = toString(10.1);
    assert(s2.compare("10.1")== 0);

    std::string s3 = toString(3.14159, 2);
    assert(s3.compare("3.14")== 0);

    std::string s4 = toString(3);
    assert(s4.compare("3")== 0);

    // split
    std::vector<std::string> sp = split("test,other,and 1 more", ",");
    assert(sp.size() == 3);
    assert(sp.at(0).compare("test") == 0);
    assert(sp.at(1).compare("other") == 0);
    assert(sp.at(2).compare("and 1 more") == 0);

    //Count char
    long c = countChar("testing.this.component.!", '.');
    assert(c == 3);
}

int testUUID() {
    cout << "Testing uuid" << endl;
    std::string* u = uuid();

    cout << *u << endl;
    cout << "out Testing uuid" << endl;
    return 0;
}

int main()
{
    testUUID();

    testDates();

    testTimes();

    testStrings();

    return 0;
}
