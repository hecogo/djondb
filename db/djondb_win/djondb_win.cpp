// djondb_win.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "util.h"
#include "service.h"

bool __stopRunning;

int _tmain(int argc, _TCHAR* argv[])
{
	__stopRunning = false;
	service_startup();

	while(true) {
		if (__stopRunning) {
			break;
		}
		Thread::sleep(30000);
	}
	return 0;
}

