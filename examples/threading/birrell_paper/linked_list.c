#include "linked_list.h"

// Function to create a new node
ListNode* create_node(char ch) {
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->ch = ch;
    new_node->next = NULL;
    return new_node;
}

// Function to print the current state of the list
void print_list(ListNode* head) {
    ListNode* current = head;
    printf("Current list: ");
    while (current != NULL) {
        printf("%c ", current->ch);
        current = current->next;
    }
    printf("\n");
}

// Function to add a new node to the head of the list
void add_to_list(ListNode** head_ref, ListNode* new_node) {
    new_node->next = *head_ref;
    *head_ref = new_node;
    print_list(*head_ref);
}

void free_list(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
}

int example() {
    // Head of the linked list
    ListNode* head = NULL;

    // Example usage
    ListNode* new_node1 = create_node('a');
    add_to_list(&head, new_node1);

    ListNode* new_node2 = create_node('b');
    add_to_list(&head, new_node2);

    ListNode* new_node3 = create_node('c');
    add_to_list(&head, new_node3);

    // Free memory
    ListNode* current = head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}