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

#include "util.h"

#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "defs.h"
#include <stdlib.h>
#include <string.h>

#ifndef WINDOWS
#include <uuid/uuid.h>
#endif
#ifdef LINUX
//#include <QX11Info>
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
#include <Rpc.h>
#include <direct.h>
#endif

bool _daemon;

void logInfo(char* text) {
    cout << text << endl;
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
    UUID uuid;

    ::UuidCreate(&uuid);
    UCHAR* wszUuid = NULL;
    ::UuidToStringA(&uuid, &wszUuid);
    std::string res;
    if(wszUuid != NULL)
    {
        char* uuid = (char*)wszUuid;
        res = string(uuid);

        ::RpcStringFree(&wszUuid);
        wszUuid = NULL;
    }

    // removes the { } characters
    res = res.substr(1, res.size() - 2);
    return new string(res);
#endif
}


bool isDaemon() {
	return _daemon;
}

void setDaemon(bool daemon) {
	_daemon = daemon;
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
    Display* display = XOpenDisplay(NULL);
    if(XScreenSaverQueryExtension(display, &event_base, &error_base))
        _idleDetectionPossible = true;
    else
        _idleDetectionPossible = false;
    _mit_info = XScreenSaverAllocInfo();

    XScreenSaverQueryInfo(display, DefaultRootWindow(display), _mit_info);

    XCloseDisplay(display);

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
#endif

    return idlesecs;
}

Version getCurrentVersion() {
    return getVersion(PACKAGE_VERSION);
}

Version getVersion(const char* version) {
    return Version(std::string(version));
}
