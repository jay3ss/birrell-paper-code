#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} node;

// source: https://stackoverflow.com/a/77835325
typedef enum { false, true } bool;

bool not(bool state) {
    return 1 - state;
}

node* node_new(int value) {
    node* n = malloc(sizeof(node));
    n->next = NULL;
    n->value = value;
    return n;
}

node* node_add(node* head, int value) {
    node* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = node_new(value);

    return temp->next;
}

node* node_find(node* head, int value) {
    bool found = false;
    node* temp = head;

    while (temp != NULL && not(found)) {
        found = temp->value == value ? true : false;
        if (not(found)) {
            temp = temp->next;
        }
    }

    return found ? temp : NULL;
}

node* node_del(node* head, int value) {
    node* temp = head;
    bool found = false;

    while (temp->next != NULL && not(found)) {
        found = (temp->next->value == value) ? true : false;
        if (not(found)) {
            temp = temp->next;
        }
    }

    if (found) {
        // take found node's next and set it to the previous node's next
        node* next = temp->next->next;
        free(temp->next);
        temp->next = next;
        return temp;
    }

    return NULL;
}

void node_print(node* head) {
    node* temp = head;

    int count = 1;
    while (temp != NULL) {
        printf("Node %i has value %i \n", count, temp->value);
        temp = temp->next;
        count++;
    }
}


int main() {
    node* head = node_new(42);
    for (int i = 0; i < head->value; i++) { node_add(head, i); }

    node_print(head);

    int value_to_find = 17;
    node* found_node = node_find(head, value_to_find);
    printf("Node with value %i %sfound.\n", 
        value_to_find, 
        found_node == NULL ? "not " : "");

    int value_to_delete = 23;
    node* deleted = node_del(head, value_to_delete);
    printf("Node with value %i found and %sdeleted.\n", 
        value_to_delete, 
        deleted == NULL ? "not " : "");

    node_print(head);

    return 0;
}