// Mutual exclusion. Here's the code in Modula-2+:

// TYPE List = REF RECORD ch: CHAR; next: List END;
// VAR m: Thread.Mutex;
// VAR head: List;

// LOCK m DO
//     newElement^.next := head;
//     head := newElement;
// END;
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

// define the Thread type (similar to Modula-2+'s TYPE Thread)
typedef pthread_t Thread;

// define the Mutex type
typedef pthread_mutex_t Mutex;

// define the Mutex and List variables
Mutex mutex;
ListNode* head = NULL;

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

void lock_mutex() {
    pthread_mutex_lock(&mutex);
}

void unlock_mutex() {
    pthread_mutex_unlock(&mutex);
}

void* threaded_add_node(void* new_node) {
    lock_mutex();

    ListNode* node = (ListNode*)new_node;

    add_to_list(&head, node);

    unlock_mutex();

    return head;
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

int main(int argc, char* argv[]) {
    pthread_mutex_init(&mutex, NULL);
    Thread t;

    t = Fork(threaded_add_node, create_node('a'));
    // ListNode* new_node = (ListNode*)Join(t);
    Join(t);

    t = Fork(threaded_add_node, create_node('b'));
    Join(t);

    t = Fork(threaded_add_node, create_node('c'));
    Join(t);

    free_list(head);

    return 0;
}