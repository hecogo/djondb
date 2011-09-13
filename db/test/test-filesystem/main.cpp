#include <iostream>
#include <fileinputstream.h>
#include <fileoutputstream.h>
#include <string.h>
#include <assert.h>

using namespace std;

int testFileOutputStream() {
    FileOutputStream stream("test.txt", "wb");
    stream.writeChars("Hello World!", 12);
    stream.close();
    return 0;
}

int testFileInputStream() {
    FileInputStream stream("test.txt", "rb");
    char* text = stream.readChars();

    assert(strcmp(text, "Hello World!") == 0);
    stream.close();
    return 0;
}

int main()
{
    testFileOutputStream();
    testFileInputStream();
    return 0;
}
