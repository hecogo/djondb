#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef __linux
#define LINUX
#endif

#ifndef _WIN32
#include "config.h"
#else
#define PACKAGE_VERSION "0.1"
#endif

/*
#if defined Q_WS_MAC
#define MAC
#endif
#if defined Q_WS_WIN
#define WINDOWS
#endif
#if defined Q_WS_X11
#define LINUX
#endif
*/

//#define VERSION "1.2.20110726"

// #define TESTING

#endif // DEFS_H_INCLUDED
