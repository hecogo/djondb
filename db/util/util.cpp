#include "util.h"

#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "config.h"
#include <stdlib.h>
#include <string.h>

#ifndef WINDOWS
#include <uuid/uuid.h>
#endif
#ifdef LINUX
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/scrnsaver.h>
#endif
#ifdef MAC
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <IOKit/IOKitLib.h>
#endif
#ifdef WINDOWS
#include <Windows.h>
#include <Winuser.h>
#include <QUuid>
#include <direct.h>
#endif

std::string getConfigFileName() {
    std::string* homeDir = getHomeDir();
    std::string confFileName = *homeDir + "/.djon/djon.conf";
    delete (homeDir);
    return confFileName;
}

std::string toString(double a) {
    std::stringstream ss;

    ss << a;
    string res = ss.str();
    return res;
}

std::string toString(double a, int fixedPrecision) {
    std::stringstream ss;

    ss.precision(fixedPrecision);
    ss.setf(ios::fixed,ios::floatfield);

    ss << a;
    string res = ss.str();
    return res;
}

std::string toString(int a) {
    std::stringstream ss;
    ss << a;
    string s = ss.str();
    return s;
}

void logInfo(char* text) {
    cout << text << endl;
}

bool endsWith(const char* text, const char* end) {
    if (strlen(end) > strlen(text)) {
        return false;
    }
    for (unsigned int pos = 0; strlen(end) > pos; pos++) {
        if (end[strlen(end) - pos] != text[strlen(text) - pos]) {
            return false;
        }
    }
    return true;
}

std::vector<string> split(const string str, string token) {
//    char* s = (char*) malloc(str.size());
    const char* delim = token.c_str();

    //strcpy(s, str.c_str());
    char* s = strcpy((char*)str.c_str());

    vector<string> res;
    char* ptr;
    ptr = strtok(s, delim);
    while (ptr != NULL) {
        res.push_back(string(ptr));
        ptr = strtok(NULL, delim);
    }

    free (s);
    return res;
}


long countChar(const char* s, const char c) {
    long num = 0;
    for (unsigned int x = 0; x < strlen(s); x++) {
        if (s[x] == c) {
            num++;
        }
    }
    return num;
}

std::string* uuid() {
#ifndef WINDOWS
    uuid_t t;
    uuid_generate(t);

    char ch[36];
    memset(ch, 0, 36);
    uuid_unparse(t, ch);
    string* res = new string(ch);
    return res;
#else
    QUuid uuid = QUuid::createUuid();
    QString suuid = uuid.toString();

    string res = suuid.toStdString();

    // removes the { } characters
    res = res.substr(1, res.size() - 2);
    return new string(res);
#endif
}

bool makedir(const char* path) {
#ifndef WINDOWS
    int status = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#else
    int status = mkdir(path);
#endif
    if (status != 0) {
        return false;
    } else {
        return true;
    }
}

std::string* getTempDir() {
#ifndef WINDOWS
    string* tmp = new string("/tmp");
#else
    string* tmp = new std::string(getenv("TMP"));
#endif
    return tmp;
}

std::string* getHomeDir() {
#ifndef WINDOWS
    string* home = new string(getenv("HOME"));
#else
    std::string homeDrive = std::string(getenv("HOMEDRIVE"));
    std::string homePath = std::string(getenv("HOMEPATH"));
    string* home = new string(homeDrive + homePath);
#endif
    return home;
}

char* readValue(std::string cont, std::string key) {
    hashmap* map = parseTextFormat(cont);
    std::string value = READ_ELEMENT(map, key);

    char* res = NULL;
    if (value.size() == 0) {
        res = strcpy("");
    } else {
        res = strcpy(value);
    }

    delete(map);
    return res;
}

char* readConfValue(const string& name, const char* def) {
    std::string confFileName = getConfigFileName();
    char* conf = readFile(const_cast<char*> (confFileName.c_str()));

    char* res = readValue(string(conf), name);
    if (strlen(res) == 0) {
        free(res);
        res = strcpy(def);
    }
    free(conf);
    return res;
}

string replaceValue(string cont, string key, string value) {
    int pos = cont.find(key + ":");
    string newValue = key + ":" + value + ";\n";
    if (pos != cont.npos) {
        int end = cont.find(";", pos) + 2; //; and \n
        cont = cont.replace(pos, end - pos, newValue);
    } else {
        cont = cont.append(newValue);
    }

    return cont;
}

int writeConfValue(const string& name, const string& value) {
    std::string confFileName = getConfigFileName();
    std::string conf = std::string(readFile(const_cast<char*> (confFileName.c_str())));

    conf = replaceValue(conf, name, value);

    int res = writeFile(confFileName, conf, false);

    return res;
}

void readElement(string& readed, stringstream &str) {

    int c;
    do {
        c = str.get();
        if (c != ';') {
            if ((readed.length() != 0) || ((c != 13) && (c != 10))) {
                if (str.good()) {
                    char str[2];
                    str[0] = c;
                    str[1] = '\0';
                    readed += str;
                } else {
                    break;
                }
            }
        }
    } while (c != ';');
}

void* mmalloc(size_t size) {
    void* p = malloc(size);
    if (p == NULL) {
        cout << "Out of memory!!!" << endl;
        exit(EXIT_FAILURE);
    }
    return p;
}


long idleTime() {
    long idlesecs;
#ifdef LINUX
    bool _idleDetectionPossible;
    XScreenSaverInfo *_mit_info;

    int event_base, error_base;
    if(XScreenSaverQueryExtension(QX11Info::display(), &event_base, &error_base))
        _idleDetectionPossible = true;
    else
        _idleDetectionPossible = false;
    _mit_info = XScreenSaverAllocInfo();

    XScreenSaverQueryInfo(QX11Info::display(), QX11Info::appRootWindow(), _mit_info);

    idlesecs = (_mit_info->idle/1000);

#endif
#ifdef WINDOWS

    LASTINPUTINFO lif;
    lif.cbSize = sizeof(LASTINPUTINFO);
    GetLastInputInfo(&lif);
    DWORD tickCount = GetTickCount();
    idlesecs = (tickCount - lif.dwTime) / 1000;

#endif
#ifdef MAC
    idlesecs = -1;//int64_t
    io_iterator_t iter = 0;
    if (IOServiceGetMatchingServices(kIOMasterPortDefault, IOServiceMatching("IOHIDSystem"), &iter) == KERN_SUCCESS) {
        io_registry_entry_t entry = IOIteratorNext(iter);
        if (entry) {
            CFMutableDictionaryRef dict = NULL;
            if (IORegistryEntryCreateCFProperties(entry, &dict, kCFAllocatorDefault, 0) == KERN_SUCCESS) {
                CFNumberRef obj = (CFNumberRef)CFDictionaryGetValue(dict, CFSTR("HIDIdleTime"));
                if (obj) {
                    int64_t nanoseconds = 0;
                    if (CFNumberGetValue(obj, kCFNumberSInt64Type, &nanoseconds)) {
                        idlesecs = (nanoseconds >> 30); // Divide by 10^9 to convert from nanoseconds to seconds.
                    }
                }
                CFRelease(dict);
            }
            IOObjectRelease(entry);
        }
        IOObjectRelease(iter);
    }

//    bool _idleDetectionPossible;
//    XScreenSaverInfo *_mit_info;

//    int event_base, error_base;
//    Display* display = XOpenDisplay(0);
//    if(XScreenSaverQueryExtension(display, &event_base, &error_base))
//        _idleDetectionPossible = true;
//    else
//        _idleDetectionPossible = false;
//    _mit_info = XScreenSaverAllocInfo();

//    int i = DefaultScreen(display);
//    int res = XScreenSaverQueryInfo(display, RootWindow(display, i), _mit_info);

//    if (res != 0) {
//        idlesecs = (_mit_info->idle/1000);
//    }
#endif

    return idlesecs;
}

Version getCurrentVersion() {
    return getVersion(VERSION);
}

Version getVersion(const char* version) {
    return Version(std::string(version));
}
