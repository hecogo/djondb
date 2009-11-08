/*
 * File:   threads.h
 * Author: cross
 *
 * Created on November 18, 2008, 9:42 PM
 */

#include <pthread.h>

class Thread {
private:
    int threadId;
    pthread_t internal;

public:
    void *(*runFunction)(void* arg);

    Thread(void *(*run)(void* arg));

    void start(void* arg);

    void join();
};
