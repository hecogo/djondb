#include "../util.h"
#include <iostream>

int m_numtreads;

Thread::Thread(void *(*run)(void* arg)) {
    runFunction = run;
    m_numtreads++;
    m_threadId = m_numtreads;
}

void Thread::start(void* arg) {
    int rc = pthread_create(&internal, NULL, runFunction, (void*)arg);
    if (rc) {
        cout << "Error creating the thread" << endl;
    }
}

void Thread::join() {
    pthread_join(internal, NULL);
}

Thread::~Thread() {
//    pthread_exit((void*)internal);
}