#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define QUEUE_SIZE 10

typedef struct queue
{
    int32_t data[QUEUE_SIZE];
    uint32_t rear;  // point to the next availabe cell
    uint32_t front; // point to the current element waiting in queue
    uint32_t count; // count the num of elements currently in the queue
} queue_t;

bool enqueue( queue_t* queue_ptr, int32_t value );
bool dequeue( queue_t* queue_ptr, int32_t* value );
bool queue_is_empty( queue_t* queue_ptr );
bool queue_is_full( queue_t* queue_ptr );
bool queue_init( queue_t* queue_ptr );

bool enqueue( queue_t* queue_ptr, int32_t value )
{
    if ( queue_ptr == NULL )
    {
        return false;
    }

    if( !queue_is_full(queue_ptr) )
    {
        queue_ptr->data[queue_ptr->rear] = value;
        // advance rear to point to the next available cell
        queue_ptr->rear = (queue_ptr->rear + 1) % QUEUE_SIZE;
        queue_ptr->count++;
        return true;
    }
    return false;
}

bool dequeue( queue_t* queue_ptr, int32_t* value )
{
    if ( queue_ptr == NULL || value == NULL )
    {
        return false;
    }

    if( !queue_is_empty(queue_ptr) )
    {
        *value = queue_ptr->data[queue_ptr->front];
        // advaced front to the next one in queue
        queue_ptr->front = (queue_ptr->front + 1) % QUEUE_SIZE; 
        queue_ptr->count--;
        return true;
    }
    return false;
}

bool queue_is_empty( queue_t* queue_ptr )
{
    if ( queue_ptr->count == 0 )
    {
        return true;
    }
    return false;
}

bool queue_is_full( queue_t* queue_ptr )
{
    if ( queue_ptr->count == QUEUE_SIZE )
    {
        return true;
    }
    return false;
}

bool queue_init( queue_t* queue_ptr )
{
    if ( queue_ptr == NULL )
    {
        return false;
    }

    queue_ptr->front = 0;
    queue_ptr->rear = 0;
    queue_ptr->count = 0;
    return true;
}

int main( void )
{
    queue_t queue;
    int32_t dequeue_element;
    int32_t test_arr[] = {3, 2, 8};
    uint32_t test_arr_len = sizeof(test_arr)/sizeof(test_arr[0]);

    // init queue
    if( !queue_init(&queue) )
    {
        printf("Init queue failed\n");
        return -1;
    }
    printf("Queue init successfully\n");

    // insert elements into queue
    for (uint32_t i=0; i<test_arr_len; i++)
    {
        if ( !enqueue(&queue, test_arr[i]) )
        {
            printf("Failed to enter element into queue\n");
            return -1;
        }
        printf("Added to queue: %d\n", test_arr[i]);
    }

    // dequeue elements from queue
    for (uint32_t i=0; i<test_arr_len; i++)
    {
        if ( !dequeue(&queue, &dequeue_element) )
        {
            printf("Failed to dequeue element from queue\n");
            return -1;
        }
        printf("Dequeue: %d\n", dequeue_element);
    }

    return 0;
}