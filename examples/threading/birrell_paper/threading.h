#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>

// define the Thread type (similar to Modula-2+'s TYPE Thread)
typedef pthread_t Thread;

// define the Mutex type
typedef pthread_mutex_t Mutex;

// define the Condition type
typedef pthread_cond_t Condition;

// define Forkee as a function pointer type (equivalent to Modula-2+'s Forkee)
typedef void* (*Forkee)(void* arg);

void* join(Thread thread);

// Fork function to create and start a thread (equivalent to Modula-2+'s Fork)
Thread fork_thread(Forkee proc, void* arg);

void lock_mutex();

void unlock_mutex();

void wait(Condition c, Mutex m);

void signal(Condition c);

void broadcast(Condition c);

Mutex create_mutex();

Condition create_condition();

void init_mutex(Mutex m);

void init_condition(Condition c);

void destroy_condition(Condition c);

void destroy_mutex(Mutex m);

#endif // THREADING_H