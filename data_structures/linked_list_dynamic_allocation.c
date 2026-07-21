#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int32_t value;
    struct Node* next;
} Node;

Node* allocate_node( int32_t value )
{
    Node* new_node = (Node*)malloc(sizeof(Node));

    if ( new_node == NULL )
    {
        return NULL;
    }

    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

Node* push_node_to_front( Node* head, Node* node )
{    
    if ( node == NULL )
    {
        return head;
    }

    node->next = head;
    return node;
}

Node* push_node_to_end( Node* head, Node* node )
{
    if ( node == NULL )
    {
        return head;
    }

    if ( head == NULL )
    {
        node->next = NULL;
        return node;
    }

    Node* current = head;

    while ( current->next != NULL )
    {
        current = current->next;
    }
    current->next = node;
    node->next = NULL;

    return head;
}

Node* remove_node_from_front( Node* head )
{
    if ( head == NULL )
    {
        return NULL;
    }

    Node* temp_head = head;
    head = head->next;
    temp_head->next = NULL;
    return head;
}

void print_linked_list( Node* head )
{
    if ( head == NULL )
    {
        printf("linked list is empty\n");
        return;
    }

    uint32_t i = 0;
    while ( head != NULL )
    {
        printf("Node #%u value: %d\n", i, head->value);
        head = head->next;
        i++;
    }
}

// head -> A - > B -> C -> null
// ---------------------------
// head -> C -> B-> A - > NULL

/*
key points to remember:
save next
change link
move prev
move current
*/

/*
    We want A to point to NULL (to prev).
    But if we do it first (current->next = prev),
    we will lose the connection between A and [B -> C -> NULL].

    Therefore, we first save the next node:
    next = current->next;

    Then we change the arrow of A to point to prev:
    current->next = prev;

    After that, prev moves to the current node:
    prev = current;

    And current moves to the next node:
    current = next.

    The loop stop condition is when current becomes NULL.
    We also need to reverse the connection of the last node,
    so we continue until current reaches the end of the list.

    The return pointer is prev because when current is NULL,
    prev points to the last processed node, which becomes
    the new head of the reversed linked list.
*/

Node* reverse_linked_list( Node* head )
{
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while ( current != NULL )
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

//head-> node0-> node1-> null

uint32_t linked_list_count_elemnts( Node* head )
{
    if ( head == NULL )
    {
        return 0;
    }

    uint32_t counter = 0;

    while( head != NULL )
    {
        counter++;
        head = head->next;
    }

    return counter;
}

bool get_val_by_index( Node* head, uint32_t index, uint32_t* node_val )
{
    if ( head == NULL )
    {
        return false;
    }

    uint32_t current_index = 0;

    while(head != NULL)
    {
        if ( current_index == index )
        {
            *node_val = head->value;
            return true;
        }
        head = head->next;
        current_index++;
    }
    return false;
}

bool linked_list_is_palindrome( Node* head )
{
    uint32_t num_of_nodes = linked_list_count_elemnts( head );

    uint32_t node_left;
    uint32_t node_right;

    for ( uint32_t i=0; i<(num_of_nodes/2); i++ )
    {
        if ( !get_val_by_index(head, i, &node_left) )
        {
            return false;
        }

        if ( !get_val_by_index(head, num_of_nodes-1-i, &node_right) )
        {
            return false;
        }
        
        if ( node_left != node_right )
        {
            return false;
        }
    }
    return true;
}

bool linked_list_is_palindrome_effective( Node* head )
{
    if ( head == NULL )
    {
        return false;
    }

    if ( head->next == NULL )
    {
        return true;
    }

    uint32_t index = 0;
    Node* reversed_list_head = head;
    uint32_t nodes_num = linked_list_count_elemnts(head);
    Node* prev = NULL;

    // set the address of the revered linked list head
    while(index < (nodes_num/2))
    {
        prev = reversed_list_head;
        reversed_list_head = reversed_list_head->next;
        index++;
    }
    prev->next = NULL; // cut the linked list into half (seperate it from the right list)

    prev = NULL;
    Node* current = reversed_list_head;
    Node* next = NULL;

    // reserve the right linked list
    while ( current != NULL )
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    reversed_list_head = prev;

    // compare value vs value
    while ( head != NULL && reversed_list_head != NULL )
    {
        if ( head->value != reversed_list_head->value )
        {
            return false;
        }
        head = head->next;
        reversed_list_head = reversed_list_head->next;
    }
    return true;
}

int main( void )
{
    // define an empty linked list
    Node* head = NULL;

    Node* new_node;

    int32_t test_arr[] = {4, 6, 8};
    uint32_t test_arr_len = sizeof(test_arr)/sizeof(test_arr[0]);

    uint32_t i;

    for ( i=0; i< test_arr_len; i++ )
    {
        new_node = allocate_node( test_arr[i] );
        
        if (  new_node )
        {
            printf("success creating new node\n");
        }
        else
        {
            printf("failed to create node\n");
        }

        head = push_node_to_front( head, new_node );

        if (head != NULL )
        {
            printf("Pushed node with value: %d\n", test_arr[i]);
        }
    }

    print_linked_list( head );

    printf("\nremoving nodes\n\n");

    for ( i=0; i< test_arr_len; i++ )
    {
        head = remove_node_from_front( head );
        print_linked_list( head );
        printf("\n");
    }

    return 0;
}   