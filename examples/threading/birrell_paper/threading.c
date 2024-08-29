#include <stdlib.h>
#include "threading.h"

// Fork function to create and start a thread (equivalent to Modula-2+'s Fork)
Thread fork_thread(Forkee proc, void* arg) {
    Thread thread;
    if (pthread_create(&thread, NULL, proc, arg)) {
        exit(1);
    }

    return thread;
}

void* join(Thread thread) {
    void* result;
    if (pthread_join(thread, &result)) {
        exit(2);
    }

    return result;
}

void lock_mutex(Mutex mutex) {
    pthread_mutex_lock(&mutex);
}

void unlock_mutex(Mutex mutex) {
    pthread_mutex_unlock(&mutex);
}

void wait(Condition c, Mutex m) {
    pthread_cond_wait(&c, &m);
}

void signal(Condition c) {
    pthread_cond_signal(&c);
}

void broadcast(Condition c) {
    pthread_cond_broadcast(&c);
}

Mutex create_mutex() {
    Mutex m = PTHREAD_MUTEX_INITIALIZER;

    return m;
}

Condition create_condition() {
    Condition c = PTHREAD_COND_INITIALIZER;

    return c;
}

void init_mutex(Mutex m) {
    pthread_mutex_init(&m, NULL);
}

void init_condition(Condition c) {
    pthread_cond_init(&c, NULL);
}

void destroy_condition(Condition c) {
    pthread_cond_destroy(&c);
}

void destroy_mutex(Mutex m) {
    pthread_mutex_destroy(&m);
}