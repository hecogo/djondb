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

#include "threads.h"
#include <iostream>
#include "../defs.h"
#ifdef WINDOWS
	#include <Windows.h>
	#include <time.h>
#endif

int m_numtreads;
bool Thread::m_mutexInitalized;
pthread_mutex_t Thread::m_mutex_t;

Thread::Thread(void *(*run)(void* arg)) {
    runFunction = run;
    m_numtreads++;
    m_threadId = m_numtreads;
}

void Thread::start(void* arg) {
    int rc = pthread_create(&internal, NULL, runFunction, (void*)arg);
    if (rc) {
        throw "Error creating the thread";
    }
}

void Thread::join() {
    pthread_join(internal, NULL);
}

Thread::~Thread() {
    pthread_detach(internal);
}


void Thread::sleep(int milisecs) {
#ifndef WINDOWS
	struct timespec timeToWait;
	struct timeval now;
	int rt;

	int currentsecs;
	int currentusecs;

	SYSTEMTIME st;
	GetSystemTime(&st);
	currentsecs = st.wSecond;
	currentusecs = st.wMilliseconds / 1000; // 10^(-9)

	timeToWait.tv_sec = currentsecs;
	timeToWait.tv_nsec = (currentusecs*1000) + milisecs;

	pthread_mutex_t fakeMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t fakeCond = PTHREAD_COND_INITIALIZER;	pthread_mutex_lock(&fakeMutex);

	rt = pthread_cond_timedwait(&fakeCond, &fakeMutex, &timeToWait);
	pthread_mutex_unlock(&fakeMutex);
#else
	System::Threading::Thread::CurrentThread->Sleep(milisecs);
#endif
}


void Thread::mutex_lock() {
    if (!m_mutexInitalized) {
        pthread_mutex_init(&m_mutex_t, NULL);
        m_mutexInitalized = true;
    }
    pthread_mutex_lock(&m_mutex_t);
}

void Thread::mutex_unlock() {
    pthread_mutex_unlock(&m_mutex_t);
}

