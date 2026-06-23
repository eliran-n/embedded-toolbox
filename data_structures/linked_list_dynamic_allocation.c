#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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