#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NODES 5

typedef struct Node
{
    int32_t value;
    struct Node* next;
} Node_t;


int32_t find_free_node(bool* free_list, uint32_t size);
Node_t* allocate_node(bool* free_list, Node_t* node_pool, uint32_t pool_size, int32_t value);
Node_t* push_to_front( Node_t* head, Node_t* node);
Node_t* remove_node_from_front( Node_t* head, Node_t* node_pool, uint32_t pool_len, bool* free_list );
bool init_free_list(bool* free_list, uint32_t size);
void print_linked_list( Node_t* head );


int32_t find_free_node(bool* free_list, uint32_t size)
{
    for(uint32_t i=0; i<size; i++ )
    {
        if(free_list[i] == true)
        {
            free_list[i] = false;
            return i;
        }
    }
    return -1;
}

Node_t* allocate_node(bool* free_list, Node_t* node_pool, uint32_t pool_size, int32_t value)
{
    int32_t free_node_idx;

    free_node_idx = find_free_node(free_list, pool_size);

    if ( free_node_idx == -1 )
    {
        return NULL;
    }

    // assign the value to the free node
    node_pool[free_node_idx].value = value;
    node_pool[free_node_idx].next = NULL;

    // return the address of the free - allocated node
    return &node_pool[free_node_idx];
}

Node_t* push_to_front( Node_t* head, Node_t* node)
{
    // if node creation failed  - return head as was given
    if ( node == NULL )
    {
        return head;
    }

    node->next = head;
    return node;
}

Node_t* remove_node_from_front( Node_t* head, Node_t* node_pool, uint32_t pool_len, bool* free_list )
{
    if ( head == NULL || free_list == NULL || node_pool == NULL || pool_len == 0 )
    {
        return NULL;
    }

    // store the new head
    Node_t* new_head = head->next;

    // free the node
    for (uint32_t i=0; i<pool_len; i++)
    {
        if ( head == &node_pool[i] )
        {
            // set node as free;
            free_list[i] = true;
            break;
        }
    }

    // reset the node which removed
    head->value = 0;
    head->next = NULL;

    return new_head;
}

bool init_free_list(bool* free_list, uint32_t size)
{
    if ( free_list == NULL || size == 0 )
    {
        return false;
    }

    for(uint32_t i=0; i<size; i++)
    {
        free_list[i] = true;
    }
    return true;
}

void print_linked_list( Node_t* head )
{
    if ( head == NULL )
    {
        printf("Empty linked list.\n");
        return;
    }

    uint32_t i = 0;
    while (head != NULL)
    {
        printf("Node #%d value: %d\n", i, head->value);
        head = head->next;
        i++;
    }
}

int main( void )
{
    Node_t* head = NULL;
    Node_t node_pool[MAX_NODES];
    bool free_list[MAX_NODES];
    Node_t* new_node = NULL;

    // init pool
    if ( !init_free_list( free_list, MAX_NODES) )
    {
        printf("pool init failed.\n");
        return -1;
    }
    printf("pool succesfully initilized\n\n");

    uint32_t i;
    int32_t test_arr[]={5, 3, 7};
    uint32_t test_arr_len = sizeof(test_arr)/sizeof(test_arr[0]);

    for (i=0; i<test_arr_len; i++)
    {
        // allocate new node
        new_node = allocate_node(free_list, node_pool, MAX_NODES, test_arr[i]);

        if ( new_node == NULL )
        {
            printf("allocation failed\n");
            return -1;
        }
        // push node to front
        printf("Push node to front - val: %d\n", test_arr[i]);
        head = push_to_front(head, new_node);
    }

    // printing linked list after pushing nodes
    print_linked_list( head );
    printf("\n");

    // removing nodes
    for (i=0; i<test_arr_len; i++)
    {   
        printf("Removing node\n");
        head = remove_node_from_front( head, node_pool, MAX_NODES, free_list);

        // print linked list
        printf("Updated linked list:\n");
        print_linked_list( head );
        printf("\n");
    }

    return 0;
}