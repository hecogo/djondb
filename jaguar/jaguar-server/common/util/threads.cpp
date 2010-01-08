#include "../util.h"
#include <iostream>

int m_numtreads;

Thread::Thread(void *(*run)(void* arg)) {
    runFunction = run;
    m_numtreads++;
    m_threadId = m_numtreads;
}

void Thread::start(void* arg) {
    internal = m_numtreads;
    int rc = pthread_create(&internal, NULL, runFunction, (void*)arg);
    if (rc) {
        cout << "Error creating the thread" << endl;
    }
}

void Thread::join() {
    pthread_join(internal, NULL);
}

Thread::~Thread() {
    pthread_detach(internal);
}


static void Thread::mutex_lock() {
    if (!m_mutexInitalized) {
        pthread_mutex_init(&m_mutex_t, NULL);
        m_mutexInitalized = true;
    }
    pthread_cond_wait()
    pthread_mutex_lock(&m_mutex_t);
}

static void Thread::mutex_unlock() {
    pthread_mutex_unlock(&m_mutex_t);
}
