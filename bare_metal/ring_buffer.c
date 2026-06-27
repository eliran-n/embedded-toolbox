#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ring_buffer.h"

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