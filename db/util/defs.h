#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef __linux
#define LINUX
#endif

#ifndef _WIN32
#include "../config.h"
#else
#define PACKAGE_VERSION "0.1"
#endif

#ifdef __MACH__ || __APPLE__ || TARGET_OS_MAC
#define MAC
#endif

//#define VERSION "1.2.20110726"

// #define TESTING

#endif // DEFS_H_INCLUDED
