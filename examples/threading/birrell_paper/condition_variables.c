// Condition variables. Here's the code in Modula-2+:

// TYPE Condition;
// PROCEDURE Wait(m: Mutex; c: Condition);
// PROCEDURE Signal(c: Condition);
// PROCEDURE Broadcast(c: Condition);
// VAR nonEmpty: Thread.Condition;

// LOCK m DO
//     WHILE head = NIL DO Thread.Wait(m, nonEmpty) END;
//     topElement := head;
//     head := head^.next;
//     Thread.Signal(nonEmpty)
// END;

// NOTE: this example will run, but it hangs because nothing is being added
// to the list's head.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "threading.h"


Mutex mutex;
Condition non_empty;

ListNode* head = NULL;
bool item_available = false;

void* producer(void* args) {
    lock_mutex(mutex);

    ListNode* new_node = create_node('A' + rand() % 26);
    add_to_list(&head, new_node);
    item_available = true;

    printf("Producer: Added node with data '%c'.\n", new_node->ch);

    signal(non_empty);
    unlock_mutex(mutex);

    return NULL;
}

void* consumer() {
    lock_mutex(mutex);

    while (!item_available) {
        printf("Consumer: Waiting for item...\n");
        wait(non_empty, mutex);
    }

    printf("Consumer: Processing list...\n");
    print_list(head);

    item_available = false;

    signal(non_empty);
    unlock_mutex(mutex);

    return NULL;
}


int main(int argc, char* argv[]) {
    mutex = create_mutex();
    non_empty = create_condition();

    Thread prod_thread = fork_thread(producer, NULL);
    Thread cons_thread = fork_thread(consumer, NULL);

    join(prod_thread);
    join(cons_thread);

    destroy_mutex(mutex);
    destroy_condition(non_empty);

    free_list(head);

    return 0;
}
