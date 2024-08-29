// Thread creation. Here's the code in Modula-2+:

// TYPE Thread;
// TYPE Forkee = PROCEDURE( REFANY): REFANY;
// PROCEDURE Fork(proc: Forkee; arg: REFANY): Thread;
// PROCEDURE Join(thread: Thread): REFANY;
//
// VAR t: Thread;
// t := Fork(a, x);
// p := b(y);
// q := Join(t);
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// define the Thread type (similar to Modula-2+'s TYPE Thread)
typedef pthread_t Thread;

// define Forkee as a function pointer type (equivalent to Modula-2+'s Forkee)
typedef void* (*Forkee)(void* arg);

// Fork function to create and start a thread (equivalent to Modula-2+'s Fork)
Thread Fork(Forkee proc, void* arg) {
    Thread thread;
    if (pthread_create(&thread, NULL, proc, arg)) {
        exit(1);
    }

    return thread;
}

// Join function to wait for a thread and retrieve its result
// (equivalent to Modula-2+'s Join)
void* Join(Thread thread) {
    void* result;
    if (pthread_join(thread, &result)) {
        exit(2);
    }

    return result;
}

// example usage
void* example_func(void* arg) {
    int* x = (int*)arg;
    int* result = malloc(sizeof(int));
    *result = *x * 2; // example operation
    return result;
}

int main(int argc, char* argv[]) {
    int x = 10;

    // Fork a thread to run example_func with argument x
    Thread t = Fork(example_func, &x);

    // do other work in main thread...
    for (int num = 2, count = 0; count < 10000; num++) {
        int is_prime = 1;
        for (int i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            count++;
        }
    }

    // Join the thread and get the result
    int* q = (int*)Join(t);
    printf("Result from thread: %d\n", *q);

    // free the memory allocated in the thread
    free(q);

    return 0;
}