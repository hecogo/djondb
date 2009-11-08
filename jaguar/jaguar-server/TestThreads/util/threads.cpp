#include "threads.h"


Thread::Thread(void *(*run)(void* arg)) {
    runFunction = run;
}

void Thread::start(void* arg) {
    threadId = pthread_create(&internal, NULL, runFunction, arg);
}

void Thread::join() {
    pthread_join(internal, NULL);
}
