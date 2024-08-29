#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct ListNode {
    char ch;                // Character data
    struct ListNode* next;  // Pointer to the next node
} ListNode;

// Function to create a new node
ListNode* create_node(char ch);

// Function to print the current state of the list
void print_list(ListNode* head);

// Function to free the allocated memory
void free_list(ListNode* head);

// Function to add a new node to the head of the list
void add_to_list(ListNode** head_ref, ListNode* new_node);

